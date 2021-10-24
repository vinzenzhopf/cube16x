
#pragma once

#include <iostream>
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
    uint16_t diff = 0x20;
    uint16_t end = start + diff;
    uint16_t dt = end - start;

    TEST_ASSERT_LESS_OR_EQUAL_HEX32(start, end);
    TEST_ASSERT_EQUAL(diff, dt);
}

class A {
    public:
        virtual void print_me(void) {
            std::cout << "I'm A" << std::endl;
        }

        virtual ~A() = default;

        virtual void print_me2(void) = 0;
};

class B : public A {
    public:
        void print_me(void) override {
            A::print_me();
            std::cout << "I'm B" << std::endl;
        }

        virtual void print_me2(void){
            std::cout << "I'm B2" << std::endl;
        }
};

class IC{
    public:
        virtual void addEntry(A *a) = 0;
        virtual A* getEntry(int index) = 0;
};

class C : public IC {
    protected:
        A *entries[5];
        int index;
    public:
        C() : index(0){
        }
        ~C() = default;
    
        void addEntry(A *a) override{
            entries[index] = a;
            index++;
        }
    
        A* getEntry(int index) override{
            return entries[index];
        }
};

void test_pointer_to_objects(void) {
    //A a;
    B b;
    
    C c;
    IC *ic;
    ic = &c;

    //ic->addEntry(&a);
    ic->addEntry(&b);

    A* p = nullptr;
    //p = &a;
    // p->print_me();

    p = &b;
    p->print_me();
    p->print_me2();

    std::cout << "------" << std::endl;
    p = ic->getEntry(0);
    std::cout << (p == nullptr) << std::endl;
    p->print_me();
    p->print_me2();
    // p = ic->getEntry(1);
    // p->print_me();

}

