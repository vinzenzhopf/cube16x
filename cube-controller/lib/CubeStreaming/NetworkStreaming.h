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

class NetworkStreaming final : public CyclicModule {
    public:
        INetworkStreamAnimation * const networkStreamAnimation;
        uint8_t *mac;
        IPAddress ip;
        IPAddress dns;
        IPAddress gateway;
        IPAddress subnet;
        unsigned long timeout = 10000UL;
        unsigned long responseTime = 4000UL;
        uint32_t cycle;
        uint8_t step;
        int packetSize;

        // EthernetServer server;
        // EthernetClient client;
        EthernetUDP Udp;
        IPAddress remote;
        datagram_buffer_t receiveBuffer;  // buffer to hold incoming packet,
        datagram_buffer_t replyBuffer;    // message to send back
        uint16_t replyBufferSize;
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
                while (true) {
                    delay(1); // do nothing, no point running without Ethernet hardware
                }
            }

            Serial.println("Trying to get an IP address using DHCP");
            Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            if (Ethernet.begin(mac, timeout, responseTime) == 0) {
                Serial.println("Failed to configure Ethernet using DHCP");

                if (Ethernet.linkStatus() == LinkOFF) {
                    Serial.println("Ethernet cable is not connected.");
                }
                
                // initialize the Ethernet device not using DHCP:
                // Serial.println("Returning to fallback configuration.");
                // Ethernet.begin(mac, ip, dns, gateway, subnet);

                // Skip default Ethernet initialization.
                return;
            }
            // print your local IP address:
            Serial.println("Local IP:");
            Serial.println(Ethernet.localIP());
            Serial.println(Ethernet.subnetMask());
            Serial.println(Ethernet.gatewayIP());

            // start listening for clients
            // server.begin();
            Udp.begin(ServerPort);
            Serial.println("Server running...");
        }

        bool initialize() override{
            return true;
            step = 0;
        }
        
        void cyclic()  override{
            cycle = (cycle+1) % 1000;

            //UDP Communication
            switch(step){
                case 0:
                    packetSize = Udp.parsePacket();
                    if(packetSize){
                        // Serial.print("Received packet of size ");
                        // Serial.println(packetSize);
                        step++;
                    }    
                    break;
                case 1: 
                    // read the packet into packetBufffer
                    Udp.read(receiveBuffer.asBuffer, DATAGRAM_BUFFER_SIZE);
                    // Serial.print(Udp.remoteIP());
                    remote = Udp.remoteIP();
                    Serial.printf("[UDP] Datagram from IP:%d.%d.%d.%d Port:%d Size:%d, PacketCount=%d, PayloadType=0x%X\n", 
                       remote[0], remote[1], remote[2], remote[3],
                        Udp.remotePort(), packetSize,
                        receiveBuffer.asDatagram.header.PacketCount,
                        receiveBuffer.asDatagram.header.PayloadType);
                    step++;
                    break;
                case 2:
                    clearReplyBuffer();
                    
                    switch (receiveBuffer.asDatagram.header.PayloadType)
                    {
                        case CubeDatagramType::Discovery:
                        case CubeDatagramType::Info:
                            Serial.println("[UDP] Reply to Info Request");
                            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(InfoResponsePayload);
                            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::InfoResponse;
                            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
                            replyBuffer.asDatagram.payload.asInfoResponse.ErrorCode = CubeErrorCode::Ok;
                            replyBuffer.asDatagram.payload.asInfoResponse.RuntimeMs = millis();
                            strcpy(replyBuffer.asDatagram.payload.asInfoResponse.Version, CUBE_DATAGRAM_VERSION);
                            break;
                        
                        case CubeDatagramType::AnimationStart:
                            Serial.printf("[UDP] Starting Animation: %d\n", receiveBuffer.asDatagram.payload.asAnimationStartPayload.AnimationName);

                            networkStreamAnimation->startAnimation(receiveBuffer.asDatagram.payload.asAnimationStartPayload.FrameTimeUs);
                            
                            replyBufferSize = sizeof(CubeDatagramHeader);
                            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::AnimationStartAck;
                            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
                            break;
                        case CubeDatagramType::AnimationEnd:
                            Serial.println("[UDP] Ending Animation");

                            networkStreamAnimation->endAnimation();
                            
                            replyBufferSize = sizeof(CubeDatagramHeader);
                            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::AnimationEndAck;
                            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
                            break;
                        case CubeDatagramType::FrameData:
                            Serial.printf("[UDP] Processing Frame Number: %d\n", receiveBuffer.asDatagram.payload.asFramePayload.FrameNumber);

                            networkStreamAnimation->updateFrame(
                                    &receiveBuffer.asDatagram.payload.asFramePayload.Data, 
                                    receiveBuffer.asDatagram.payload.asFramePayload.FrameTimeUs
                            );

                            replyBufferSize = sizeof(CubeDatagramHeader);
                            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::FrameDataAck;
                            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
                            break;
                        
                    default:
                        case CubeDatagramType::ErrorResponse:
                            Serial.println("[UDP] Unknown UDP packet received. Responding with Error.");
                            replyBufferSize = sizeof(CubeDatagramHeader)+sizeof(InfoResponsePayload);
                            replyBuffer.asDatagram.header.PayloadType = CubeDatagramType::InfoResponse;
                            replyBuffer.asDatagram.header.PacketCount = receiveBuffer.asDatagram.header.PacketCount;
                            replyBuffer.asDatagram.payload.asInfoResponse.ErrorCode = CubeErrorCode::UnknownPackage;
                            replyBuffer.asDatagram.payload.asInfoResponse.RuntimeMs = millis();
                            strcpy(replyBuffer.asDatagram.payload.asInfoResponse.Version, CUBE_DATAGRAM_VERSION);
                            break;
                    }
                    step++;
                    break;
                case 3:
                    // send a reply to the IP address and port that sent us the packet we received
                    // Serial.println("Sending answer");
                    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

                    Udp.write(replyBuffer.asBuffer, replyBufferSize);
                    Udp.endPacket();

                    step = 0;
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
            memset(replyBuffer.asBuffer, 0, DATAGRAM_BUFFER_SIZE);
        }     
    private:  
};

