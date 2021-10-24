

#include <unity.h>

#include "test1.h"
#include "AnimationTest.h"

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_negative_buffer_overflow);
    RUN_TEST(test_pointer_to_objects);
    RUN_TEST(AnimationTest_test_playlist_manager_get_next_entry);
    UNITY_END();

    return 0;
}