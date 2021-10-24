
#include "TeensyMock.h"

#ifdef PLATFORM_NATIVE

#include <chrono>

uint32_t teensyMockPinValues[TEENSY_PIN_COUNT];
uint32_t teensyMockPinMode[TEENSY_PIN_COUNT];

void pinMode(uint8_t pin, uint8_t mode){
    teensyMockPinMode[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val){
    teensyMockPinValues[pin] = val;
}

void digitalWriteFast(uint8_t pin, uint8_t val){
    teensyMockPinValues[pin] = val;
}

uint8_t digitalRead(uint8_t pin){
    return (uint8_t)teensyMockPinValues[pin];
}

uint8_t digitalReadFast(uint8_t pin){
    return (uint8_t)teensyMockPinValues[pin];
}

void digitalToggle(uint8_t pin){
    teensyMockPinValues[pin] = !teensyMockPinValues[pin];
}
void digitalToggleFast(uint8_t pin){
    teensyMockPinValues[pin] = !teensyMockPinValues[pin];
}

uint32_t millis()
{
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return (uint32_t)ms; 
}

// Get time stamp in microseconds.
uint32_t micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return (uint32_t)us; 
}

#endif