

#include <unity.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

// void test_function_calculator_addition(void) {
//     TEST_ASSERT_EQUAL(32, calc.add(25, 7));
// }

void test_negative_buffer_overflow(void) {
    uint16_t start = 0xFFF0;
    uint16_t end = 0x0010;
    uint16_t dt = end - start;

    TEST_ASSERT_EQUAL(0x20, dt);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_negative_buffer_overflow);
    UNITY_END();

    return 0;
}