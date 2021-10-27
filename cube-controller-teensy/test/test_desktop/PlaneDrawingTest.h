
#include <unity.h>
#include <iostream>
#include <bitset>
#include <iomanip>

#include "LedCube16x.h"
#include "CubeCore.h"

#include "FrameBuffer.h"
#include "IPinChangeCallback.h"

#include "Drawing/PlaneOutputWriter.h"

namespace PlaneDrawingTest
{
    buffer_t testBuffer;
    BufferUtil testBufferUtil(&testBuffer);

    const uint8_t CLK_PIN = 0;
    const uint8_t STO_PIN = 1;
    const uint8_t DAT_PIN = 2;

    uint8_t clockCounter;
    uint32_t planeData; 
    bool stoTriggered;

    class PinChangeCallback final : public IPinChangeCallback {
        void pinChange(EPinChangeType type, uint8_t pin, uint8_t val) override{
            if(type == EPinChangeType::eSet || type == EPinChangeType::eToggle){
                if(pin == CLK_PIN && val){
                    //Rising Edge on Clock Pin
                    uint8_t dataPin = !!digitalRead(DAT_PIN);
                    // std::cout << "CLK RTRIG Count: " << std::setw (3) << (int)clockCounter;
                    // std::cout << " DATA-Pin: " << (int)dataPin;
                    planeData |= (dataPin<<clockCounter);
                    // std::cout << " PlaneData: 0b" << std::bitset<32>{planeData} << std::endl;
                    clockCounter++;
                }
                if(pin == STO_PIN && val){
                    //Rising Edge on Store Pin
                    stoTriggered = true;
                    std::cout << "STO RTRIG Count: " << std::setw (3) << (int)clockCounter;
                    std::cout << " PlaneData: 0b" << std::bitset<32>{planeData} << std::endl;
                }
            }
        }
    } pinChangeCallback;

    //std::cout << "-> Pin Change - Mode: " << (int)type << " Pin: " << (int)pin << " Value: " << (int) val << std::endl;

    PlaneOutputWriter planeOutputWriter(
        CLK_PIN, STO_PIN, DAT_PIN, 0);

    bool PlaneDrawingTest_write_plane(uint32_t requestedPlane){
        //Init data
        planeData = 0;
        clockCounter = 0;
        stoTriggered = false;

        planeOutputWriter.initialize();
        
        int state = 0;
        int iterationCount = 0;
        while(state < 4 && iterationCount < 500){
            planeOutputWriter.cyclic();
            iterationCount++;
            switch (state)
            {
            case 0:
                state++;
                break;
            case 1:
                if(planeOutputWriter.isReadyForNextPlane()){
                    planeOutputWriter.setPlaneNumber(requestedPlane);
                    state++;
                }
                break;
            case 2:
                if(planeOutputWriter.isReadyToLatch()){
                    planeOutputWriter.latchData();
                    state++;
                }
                break;
            case 3:
                if(planeOutputWriter.isReadyForNextPlane()){
                    state++;
                }
            }
        }

        TEST_ASSERT_LESS_THAN_MESSAGE(500, iterationCount, "Iteration not ended in 100 cycles!");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(4, state, "state");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(true, stoTriggered, "stoTriggered");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(16, clockCounter, "clockCounter");

        TEST_ASSERT_EQUAL_INT32_MESSAGE((1<<requestedPlane), planeData, "planeData");
        return true;
    }

    void PlaneDrawingTest_write_planes(){
        for(int i = 0; i < 16; i++){
            TEST_ASSERT_MESSAGE(PlaneDrawingTest_write_plane(i), "Writing plane i=" + i);
        }
    }

    void setUp() {
        addPinChangeCallback(&pinChangeCallback);

    }

    void tearDown() {
        removePinChangeCallback(&pinChangeCallback);
    }

    void runTests(){
        RUN_TEST(PlaneDrawingTest_write_planes);
    }
}
