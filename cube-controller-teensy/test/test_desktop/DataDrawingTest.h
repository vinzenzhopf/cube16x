
#include <unity.h>
#include <iostream>
#include <bitset>
#include <iomanip>

#include "LedCube16x.h"
#include "CubeCore.h"

#include "FrameBuffer.h"
#include "IPinChangeCallback.h"

#include "Drawing/PlaneDataOutputWriter.h"

namespace DataDrawingTest
{
    buffer_t testBuffer;
    BufferUtil testBufferUtil(&testBuffer);

    const uint8_t CLK_PIN = 0;
    const uint8_t STO_PIN = 1;
    const uint8_t DAT_PIN_START = 2;

    uint8_t clockCounter;
    uint64_t rowDriverData[SHIFT_REGISTER_LANE_COUNT]; 
    bool stoTriggered;

    void handleClockTrigger(uint8_t pin){
        uint64_t dataPin = !!digitalRead(pin);
        uint8_t index = pin - DAT_PIN_START;
        rowDriverData[index] <<= 1;
        rowDriverData[index] |= dataPin;
    }

    uint8_t getDataPinsData(){
        uint8_t data = 0;
        for(int i = 0; i < 8; i++){
            data |= ((!!digitalRead(i + DAT_PIN_START)) << i);
        }
        return data;
    }

    void printPlane(plane_t* plane){
        std::cout << "-- Plane: ---------------------------------------" << std::endl;
        std::cout << "_  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f" << std::endl;
        for(uint8_t i = 0; i < PLANE_ROW_SIZE; i++){
            row_t row = plane->asRows[i];
            std::cout << std::hex << (int)i;
            for(uint8_t j = 0; j < PLANE_ROW_SIZE; j++){
                std::cout << "  " << (int)(!!(row&(1<<j)));
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------------------------------------" << std::endl;
    }

    class PinChangeCallback final : public IPinChangeCallback {
        void pinChange(EPinChangeType type, uint8_t pin, uint8_t val) override{
            if(type == EPinChangeType::eSet || type == EPinChangeType::eToggle){
                if(pin == CLK_PIN && val){
                    uint8_t data = getDataPinsData();
                    std::cout << "CLK RTRIG with Data: 0x" << std::bitset<8>{data} << 
                            " ClockCounter: " << std::setw (3) << (int)clockCounter << endl;
                    for(uint8_t i = 0; i < SHIFT_REGISTER_LANE_COUNT; i++){
                        handleClockTrigger(i);
                    }
                    clockCounter++;
                }
                if(pin == STO_PIN && val){
                    //Rising Edge on Store Pin
                    stoTriggered = true;
                    std::cout << std::endl << "STO RTRIG Count: " << std::setw (3) << (int)clockCounter << std::endl;
                    for(uint8_t i = 0; i < SHIFT_REGISTER_LANE_COUNT; i++){
                        uint16_t data[4];
                        memcpy(data, &rowDriverData[i], 8);
                        std::cout << "\t PlaneData: 0b" << 
                                std::bitset<16>{data[3]} << " " <<
                                std::bitset<16>{data[2]} << " " << 
                                std::bitset<16>{data[1]} << " " <<
                                std::bitset<16>{data[0]} << std::endl;
                    }
                }
            }
        }
    } pinChangeCallback;

    //std::cout << "-> Pin Change - Mode: " << (int)type << " Pin: " << (int)pin << " Value: " << (int) val << std::endl;

    PlaneDataOutputWriter writer(
        CLK_PIN, STO_PIN, DAT_PIN_START, 0);

    bool write_plane_data(plane_t *plane){
        std::cout << "### Write Plane Data Start ###" << endl;
        //Init data
        memset(&rowDriverData, 0, sizeof(uint64_t)*SHIFT_REGISTER_LANE_COUNT);
        clockCounter = 0;
        stoTriggered = false;

        writer.initialize();
        
        int state = 0;
        int iterationCount = 0;
        while(state < 4 && iterationCount < 500){
            writer.cyclic();
            switch (state)
            {
            case 0:
                state++;
                break;
            case 1:
                if(writer.isReadyForNextPlane()){
                    writer.setPlane(plane);
                    state++;
                }
                break;
            case 2:
                if(writer.isReadyToLatch()){
                    writer.latchData();
                    state++;
                }
                break;
            case 3:
                if(writer.isReadyForNextPlane()){
                    state++;
                }
            }
            iterationCount++;
        }
        std::cout << "Plane written in " << iterationCount << " cycles." << std::endl;
        TEST_ASSERT_LESS_THAN_MESSAGE(500, iterationCount, "Iteration not ended in 100 cycles!");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(4, state, "state");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(true, stoTriggered, "stoTriggered");
        TEST_ASSERT_EQUAL_INT8_MESSAGE(32, clockCounter, "clockCounter");

        //TEST_ASSERT_EQUAL_INT32_MESSAGE((1<<requestedPlane), planeData, "planeData");
        std::cout << "################### End ###" << endl;
        return true;
    }

    void clearPlane(plane_t* plane){
        memset(plane, 0, sizeof(plane_t));
    }

    void DataDrawingTest_write_single_led(){
        addPinChangeCallback(&pinChangeCallback);

        plane_t plane;
        for(uint64_t led = 192; led < 193; led++){
            std::cout << "##############################" << endl;
            std::cout << "### Write LED #" << led << " Data Start ###" << endl;

            //Generate Plane
            clearPlane(&plane);
            plane.asBytes[(led / 8)] |= 1<<(led % 8);
            printPlane(&plane);
            
            //Write PlaneData to output Pins
            write_plane_data(&plane);

            //Verify Written Data
            uint32_t driverIndex = led / SHIFT_REGISTER_DEPTH;
            uint32_t ledOffset = led % SHIFT_REGISTER_DEPTH;
            for(uint32_t j = 0; j < SHIFT_REGISTER_LANE_COUNT; j++){
                //TBD rows nach rechts oder rows nach hinten? eitentlich nach hinten? d.h. x achse geht nach hinten? oder nach vorne?
                //Fix tihs.
                int64_t isRelevantLane = !!(j == driverIndex);
                int64_t expectedData = (isRelevantLane << ledOffset);
                TEST_ASSERT_EQUAL_UINT64_MESSAGE(expectedData, rowDriverData[j], "Driver Lane not as expected");
            }
        }
    }

    // void DataDrawingTest_write_planeData(){



    //     for(int i = 0; i < 1; i++){
    //         write_plane_data()

    //         TEST_ASSERT_MESSAGE(PlaneDrawingTest_write_plane(i), "Writing plane i=" + i);
    //     }
    // }

    void DataDrawingTest_write_cube(){
        TEST_ASSERT_TRUE(false);
    }

    void setUp() {
        //addPinChangeCallback(&pinChangeCallback);
    }

    void tearDown() {
        removePinChangeCallback(&pinChangeCallback);
    }

    void runTests(){
        RUN_TEST(DataDrawingTest_write_single_led);
        // RUN_TEST(DataDrawingTest_write_cube);
    }
}
