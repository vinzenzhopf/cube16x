
#pragma once

#include <unity.h>
#include <iostream>

#include "LedCube16x.h"

using namespace std;

namespace ConstantsTest
{
    void ConstantsTest_check_sizes_general_16x_cube() {
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(16,    CUBE_EDGE_SIZE,     "CUBE_EDGE_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(256,   PLANE_LED_COUNT,    "PLANE_LED_COUNT");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(4096,  TOTAL_LED_COUNT,    "TOTAL_LED_COUNT");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(16,    PLANE_COUNT,        "PLANE_COUNT");

        TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, sizeof(byte_t),   "sizeof(row_t)");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, sizeof(row_t),   "sizeof(row_t)");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, sizeof(word_t),   "sizeof(row_t)");
    }

    void ConstantsTest_check_sizes_plane_type_16x_cube() {
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(32,    PLANE_BYTE_SIZE,    "PLANE_BYTE_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(16,    PLANE_ROW_SIZE,     "PLANE_ROW_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(8,     PLANE_WORD_SIZE,    "PLANE_WORD_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(PLANE_BYTE_SIZE, sizeof(plane_t),   "sizeof(plane_t)");
    }

    void ConstantsTest_check_sizes_buffer_type_16x_cube() {
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(512,   BUFFER_BYTE_SIZE,   "BUFFER_BYTE_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(256,   BUFFER_ROW_SIZE,    "BUFFER_ROW_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(128,   BUFFER_WORD_SIZE,   "BUFFER_WORD_SIZE");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(16,    BUFFER_PLANE_COUNT, "BUFFER_PLANE_COUNT");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(BUFFER_BYTE_SIZE, sizeof(buffer_t), "sizeof(buffer_t)");
    }

    void ConstantsTest_check_data_output_sizes_16x_cube(){
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(8, SHIFT_REGISTER_LANE_COUNT, "SHIFT_REGISTER_LANE_COUNT");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(32, SHIFT_REGISTER_DEPTH, "SHIFT_REGISTER_DEPTH");
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, SHIFT_REGISTER_DEPTH_BYTES, "SHIFT_REGISTER_DEPTH_BYTES");
    }
    
    void runTests(){
        RUN_TEST(ConstantsTest_check_sizes_general_16x_cube);
        RUN_TEST(ConstantsTest_check_sizes_plane_type_16x_cube);
        RUN_TEST(ConstantsTest_check_sizes_buffer_type_16x_cube);
        RUN_TEST(ConstantsTest_check_data_output_sizes_16x_cube);
    }
}
