/*
 * NetworkStreaming.h
 *
 * Created: 08.06.2023 14:26
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "LedCube16x.h"
#include "Base/CyclicModule.h"
#include "NativeEthernet.h"
#include "CubeDatagrams.h"
#include "Animations/NetworkStream/INetworkStreamAnimation.h"
#include "Util/ToC.h"

enum NetworkStreamingStep : uint8_t
{
    OFFNoHardware       = 0,
    NoLink              = 1,
    SetupIP             = 2,
    SetupIPReset        = 3,
    SetupIPRunning      = 4,
    

    CheckLink           = 5,

    ConnectedIdle       = 10,
    ReadFrame           = 11,
    ProcessDatagram     = 12,
    SendReply           = 13
};


class NetworkStreaming final : public CyclicModule {
    public:
        INetworkStreamAnimation * const networkStreamAnimation;
        uint8_t *mac;
        IPAddress ip;
        IPAddress dns;
        IPAddress gateway;
        IPAddress subnet;
        unsigned long timeout = 10000UL;
        unsigned long responseTime = 3000UL;
        uint32_t cycle;
        NetworkStreamingStep step;
        ToC<NetworkStreamingStep> stepEntry;
        int packetSize;
        uint32_t noMessageCounter;

        // EthernetServer server;
        // EthernetClient client;
        EthernetUDP Udp;
        IPAddress remote;
        request_datagram_buffer_t receiveBuffer;  // buffer to hold incoming packet,
        response_datagram_buffer_t replyBuffer;    // message to send back
        uint16_t replyBufferSize;

        uint32_t lastPackageCount;
        uint32_t lastFrameCount;
        uint32_t lastFrameTicksLocal;
        uint32_t lastFrameTicksSender;
        bool packageCountValid;
    protected:
    private:

	public:
        NetworkStreaming(INetworkStreamAnimation * const networkStreamAnimation, 
                         uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet, int serverPort) :
                         networkStreamAnimation(networkStreamAnimation),
                         mac(mac), ip(ip), dns(dns), gateway(gateway), subnet(subnet),
                         // server(serverPort) 
                         Udp()
        {
        }
        ~NetworkStreaming() = default;

        void setup() override{
            // start the Ethernet connection:
            Serial.println("Initializing Network...");

            // Check for Ethernet hardware present
            if (Ethernet.hardwareStatus() == EthernetNoHardware) {
                Serial.println("Ethernet hardware not detected.  Sorry, can't run without hardware. :(");
                // while (true) {
                //     delay(1); // do nothing, no point running without Ethernet hardware
                // }
                step = NetworkStreamingStep::OFFNoHardware;
                return;
            }

            if(setupNetwork()){
                step = NetworkStreamingStep::ConnectedIdle;
            }else{
                step = NetworkStreamingStep::NoLink;
            }
        }

        bool setupNetwork() {
            Serial.println("Trying to get an IP address using DHCP");
            Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            if (Ethernet.begin(mac, timeout, responseTime) == 0) {
                Serial.println("Failed to configure Ethernet using DHCP");

                if (Ethernet.linkStatus() == EthernetLinkStatus::LinkOFF) {
                    Serial.println("Ethernet cable is not connected.");
                }
                
                // initialize the Ethernet device not using DHCP:
                // Serial.println("Returning to fallback configuration.");
                // Ethernet.begin(mac, ip, dns, gateway, subnet);

                // Skip default Ethernet initialization.
                return false;
            }

            // print your local IP address:
            Serial.println("Local IP:");
            Serial.println(Ethernet.localIP());
            Serial.println(Ethernet.subnetMask());
            Serial.println(Ethernet.gatewayIP());

            // start listening for clients
            // server.begin();
            Udp.begin(ServerPort);
            Serial.printf("Server running on Port %d...\n", ServerPort);
            return true;
        }

        bool initialize() override{
            return true;
        }
        
        void cyclic()  override{
            cycle = (cycle+1) % 1000;
            stepEntry.call(step);
            if(stepEntry.Q && step < NetworkStreamingStep::CheckLink){
                Serial.printf("NetworkStreamingStep: %d\n");
            }

            //UDP Communication
            switch(step){
                case NetworkStreamingStep::OFFNoHardware:
                    Serial.println("NetworkStreamingStep: OFFNoHardware");
                    //No Network hardware. Do nothing.
                    break;

                case NetworkStreamingStep::NoLink:
                    // Serial.println("NetworkStreamingStep: No Link");
                    if (Ethernet.linkStatus() == EthernetLinkStatus::LinkON) {
                        Serial.println("Ethernet cable is connected.");
                        step = NetworkStreamingStep::SetupIP;
                    }
                    break;

                case NetworkStreamingStep::SetupIP:
                    Serial.println("NetworkStreamingStep: Setup IP");
                    //Disable output via watchdog
                    bModuleOk = false;
                    step = NetworkStreamingStep::SetupIPReset;
                    break;

                case NetworkStreamingStep::SetupIPReset:
                    Serial.println("NetworkStreamingStep: Setup IP Reset");
                    if(setupNetwork()){
                        step = NetworkStreamingStep::SetupIPRunning;
                        bModuleOk = true;
                    }else{
                        step = NetworkStreamingStep::NoLink;
                        bModuleOk = true;
                    }
                    break;

                case NetworkStreamingStep::SetupIPRunning:
                    Serial.println("NetworkStreamingStep: Setup IP Running");
                    Ethernet.maintain();
                    step = NetworkStreamingStep::ConnectedIdle;
                    break;

                case NetworkStreamingStep::ConnectedIdle:
                    // Serial.println("NetworkStreamingStep: ConnectedIdle");
                    packetSize = Udp.parsePacket();
                    if(packetSize){
                        Serial.print("Received packet of size ");
                        Serial.println(packetSize);
                        step = NetworkStreamingStep::ReadFrame;
                    }else{
                        if(stepEntry.Q){
                            noMessageCounter = 0;
                        }
                        noMessageCounter++;
                        if(++noMessageCounter > 100000){ // ca. 4x die sekunde.
                            step = NetworkStreamingStep::CheckLink;
                        }
                    }
                    break;

                case NetworkStreamingStep::CheckLink:
                    // Serial.println("NetworkStreamingStep: CheckLink");
                    if (Ethernet.linkStatus() == EthernetLinkStatus::LinkOFF) {
                        Serial.println("Ethernet cable is not connected.");
                        step = NetworkStreamingStep::NoLink;
                    }else{
                        step = NetworkStreamingStep::ConnectedIdle;
                    }
                    break;

                case NetworkStreamingStep::ReadFrame: 
                    Serial.println(1);
                    // read the packet into packetBufffer
                    Udp.read(receiveBuffer.asBuffer, DATAGRAM_BUFFER_SIZE);
                    // Serial.print(Udp.remoteIP());
                    remote = Udp.remoteIP();
                    Serial.printf("[UDP] Datagram from IP:%d.%d.%d.%d Port:%d Size:%d, PacketCount=%d, PayloadType=0x%X\n", 
                       remote[0], remote[1], remote[2], remote[3],
                        Udp.remotePort(), packetSize,
                        receiveBuffer.asDatagram.header.PacketCount,
                        receiveBuffer.asDatagram.header.PayloadType);
                    step = NetworkStreamingStep::ProcessDatagram;
                    break;

                case NetworkStreamingStep::ProcessDatagram:
                    Serial.println(2);
                    clearReplyBuffer();
                    processDatagram();
                    step = NetworkStreamingStep::SendReply;
                    break;

                case NetworkStreamingStep::SendReply:
                    Serial.println(3);
                    // send a reply to the IP address and port that sent us the packet we received
                    // Serial.println("Sending answer");
                    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

                    Udp.write(replyBuffer.asBuffer, replyBufferSize);
                    Udp.endPacket();

                    step = NetworkStreamingStep::ConnectedIdle;
                    break;
            }

            //TCP Communication
            //Does not work within cyclic context. Calls Methods, that are blocking cannot be used with this program :/
            //client.connected() calls available() internally, which is blocking internally until the server has received anything from the socket.
            // if(!client){
            //     client = server.available();
            //     if(client){
            //         Serial.println("New client connected");
            //     }
            //     return;
            // }
            // if(client.connected()){
            //     // if(client.peek() > 0){
            //     //     char c = client.read();
            //     //     Serial.write(c);
            //     // }
            //     if(cycle == 0){
            //         client.println("Hello World!");
            //     }
            // }else{
            //     // client.stop();
            //     Serial.println("not available");
            // }
        }

    protected:   

        void clearReplyBuffer(){
            memset(replyBuffer.asBuffer, 0, RESPONSE_DATAGRAM_BUFFER_SIZE);
        }     

        void processDatagram(){

            packageCountValid = (lastPackageCount+1) != receiveBuffer.asDatagram.header.PacketCount;

            switch (receiveBuffer.asDatagram.header.PayloadType)
            {
                case CubeDatagramType::Discovery:
                case CubeDatagramType::Info:
                    processInfoDatagram();
                    break;
                
                case CubeDatagramType::AnimationStart:
                    processAnimationStartDatagram();
                    break;
                case CubeDatagramType::AnimationEnd:
                    processAnimationEndDatagram();
                    break;
                case CubeDatagramType::FrameData:
                    processFrameDatagram();
                    break;
                
            default:
                case CubeDatagramType::ErrorResponse:
                    processErrorDatagram();
                    break;
            }

            lastPackageCount = receiveBuffer.asDatagram.header.PacketCount;
        }

        void processInfoDatagram(){
            Serial.println("[UDP] Reply to Info Request");

            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(InfoResponsePayload);
            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::InfoResponse;
            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
            replyBuffer.asDatagram.payload.asInfoResponse.ErrorCode = CubeErrorCode::Ok;
            replyBuffer.asDatagram.payload.asInfoResponse.CurrentTicks = millis();
            strcpy(replyBuffer.asDatagram.payload.asInfoResponse.Version, CUBE_DATAGRAM_VERSION);
        }

        void processErrorDatagram(){
            Serial.println("[UDP] Unknown UDP packet received. Responding with Error.");

            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(InfoResponsePayload);
            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::InfoResponse;
            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
            replyBuffer.asDatagram.payload.asInfoResponse.ErrorCode = CubeErrorCode::UnknownPackage;
            replyBuffer.asDatagram.payload.asInfoResponse.CurrentTicks = millis();
            strcpy(replyBuffer.asDatagram.payload.asInfoResponse.Version, CUBE_DATAGRAM_VERSION);
        }

        void processAnimationStartDatagram(){
            Serial.printf("[UDP] Starting Animation: %d\n", receiveBuffer.asDatagram.payload.asAnimationStartPayload.AnimationName);

            networkStreamAnimation->startAnimation(receiveBuffer.asDatagram.payload.asAnimationStartPayload.FrameTimeUs);
            
            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(AnimationStartResponsePayload);
            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::AnimationStartAck;
            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
            replyBuffer.asDatagram.payload.asAnimationStartResponse.CurrentTicks = millis();
        }

        void processAnimationEndDatagram(){
            Serial.println("[UDP] Ending Animation");

            networkStreamAnimation->endAnimation();
            
            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(AnimationEndResponsePayload);
            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::AnimationEndAck;
            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
            replyBuffer.asDatagram.payload.asAnimationEndResponse.CurrentTicks = millis();
        }

        void processFrameDatagram(){
            Serial.printf("[UDP] Processing Frame Number: %d\n", receiveBuffer.asDatagram.payload.asFramePayload.FrameNumber);

            networkStreamAnimation->updateFrame(
                    &receiveBuffer.asDatagram.payload.asFramePayload.Data, 
                    receiveBuffer.asDatagram.payload.asFramePayload.FrameTimeUs,
                    receiveBuffer.asDatagram.payload.asFramePayload.FrameNumber
            );

            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(FrameResponsePayload);
            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::FrameDataAck;
            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
            replyBuffer.asDatagram.payload.asFrameResponse.CurrentTicks = millis();
            replyBuffer.asDatagram.payload.asFrameResponse.FrameNumber = 
                                    receiveBuffer.asDatagram.payload.asFramePayload.FrameNumber;
            replyBuffer.asDatagram.payload.asFrameResponse.ReceivedTicks = 
                                    receiveBuffer.asDatagram.payload.asFramePayload.CurrentTicks;
            replyBuffer.asDatagram.payload.asFrameResponse.Status = networkStreamAnimation->getAnimationStatus();
            
            if(packageCountValid){
                replyBuffer.asDatagram.payload.asFrameResponse.Status |= NetworkStreamAnimationStatus::PackageLost;
            }
            
            lastFrameCount = receiveBuffer.asDatagram.payload.asFramePayload.FrameNumber;
            lastFrameTicksLocal = replyBuffer.asDatagram.payload.asFrameResponse.CurrentTicks;
            lastFrameTicksSender = receiveBuffer.asDatagram.payload.asFramePayload.CurrentTicks;
        }

    private:  
};

