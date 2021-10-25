
#include <unity.h>
#include <iostream>

#include "LedCube16x.h"
#include "CubeCore.h"

#include "FrameBuffer.h"

namespace DrawingTest
{
    buffer_t testBuffer;
    BufferUtil testBufferUtil(&testBuffer);

    void DrawingTest_buffer_asPlanes(){
        testBufferUtil.clearBuffer();
    }

    void setUp() {
    }

    void tearDown() {
    }

    void runTests(){
        RUN_TEST(DrawingTest_buffer_asPlanes);
    }
}
