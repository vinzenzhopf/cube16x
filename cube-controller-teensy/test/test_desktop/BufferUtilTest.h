
#include <unity.h>
#include <iostream>

#include "LedCube16x.h"
#include "CubeCore.h"

#include "FrameBuffer.h"

namespace BufferUtilTest
{
    buffer_t testBuffer;
    BufferUtil testBufferUtil(&testBuffer);

    void BufferUtilTest_set_pin_by_index(){
        //First Row
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000000 ,testBuffer.asBytes[0], "");
        testBufferUtil.setLed(0, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[0], "Index: 0");

        testBufferUtil.setLed(7, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000001 ,testBuffer.asBytes[0], "Index: 7");
        
        testBufferUtil.setLed(8, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[1], "Index: 8");

        //Second Row
        testBufferUtil.setLed(16, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[2], "Index: 16");
        testBufferUtil.setLed(31, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000000 ,testBuffer.asBytes[3], "Index: 31");

        //End of first Plane
        testBufferUtil.setLed(255, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000000 ,testBuffer.asBytes[31], "Index: 255");

        //Second Plane
        testBufferUtil.setLed(256, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[32], "Index: 256");

        testBufferUtil.setLed(263, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000001 ,testBuffer.asBytes[32], "Index: 263");
        
        testBufferUtil.setLed(264, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[33], "Index: 264");

        //Last Plane First Row
        testBufferUtil.setLed(3840, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[480], "Index: 3840");

        testBufferUtil.setLed(3847, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000001 ,testBuffer.asBytes[480], "Index: 3847");
        
        testBufferUtil.setLed(3848, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000001 ,testBuffer.asBytes[481], "Index: 3848");

        //Last Byte
        testBufferUtil.setLed(4095, true);
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b10000000 ,testBuffer.asBytes[511], "Index: 4095");
    }

    void setUp() {
        testBufferUtil.clearBuffer();
    }

    void tearDown() {
    }

    void runTests(){
        RUN_TEST(BufferUtilTest_set_pin_by_index);
    }
}