

#include <unity.h>


#include "ConstantsTest.h"
#include "BufferUtilTest.h"
#include "DrawingTest.h"
#include "test1.h"
//#include "AnimationTest.h"
#include "PlaylistManagerTest.h"

void setUp(void) {
    BufferUtilTest::setUp();
    DrawingTest::setUp();
}

void tearDown(void) {
    BufferUtilTest::tearDown();
    DrawingTest::tearDown();
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    ConstantsTest::runTests();
    BufferUtilTest::runTests();
    DrawingTest::runTests();
    
    //test1.h
    // RUN_TEST(test_negative_buffer_overflow);
    // RUN_TEST(test_pointer_to_objects);

    //PlaylistMangerTest.h
    // RUN_TEST(PlaylistManagerTest_get_current_animation);
    // RUN_TEST(PlaylistManagerTest_get_next_entry);

    UNITY_END();

    return 0;
}