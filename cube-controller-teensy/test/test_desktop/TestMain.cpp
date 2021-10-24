

#include <unity.h>


#include "test1.h"
//#include "AnimationTest.h"
#include "PlaylistManagerTest.h"

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_negative_buffer_overflow);
    RUN_TEST(test_pointer_to_objects);
    RUN_TEST(PlaylistManagerTest_get_current_animation);
    RUN_TEST(PlaylistManagerTest_get_next_entry);
    UNITY_END();

    return 0;
}