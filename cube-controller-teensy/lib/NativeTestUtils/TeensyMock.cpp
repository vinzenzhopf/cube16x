
#include "TeensyMock.h"

#ifdef PLATFORM_NATIVE

#include <chrono>
#include <vector>

uint32_t teensyMockPinValues[TEENSY_PIN_COUNT];
uint32_t teensyMockPinMode[TEENSY_PIN_COUNT];
std::vector<IPinChangeCallback*> pinChangeCallbacks;

void updatePinChangeCallbacks(EPinChangeType type, uint8_t pin, uint8_t val){
    for(std::vector<IPinChangeCallback*>::iterator it = std::begin(pinChangeCallbacks); 
            it != std::end(pinChangeCallbacks); ++it) {
        if(*it){
            (*it)->pinChange(type, pin, val);
        }
    }
}

void addPinChangeCallback(IPinChangeCallback *callback){
    pinChangeCallbacks.push_back(callback);
}

void removePinChangeCallback(IPinChangeCallback *callback){
    auto it = pinChangeCallbacks.begin();
    while (it != pinChangeCallbacks.end())
    {
        if (*it && *it == callback)
        {
            pinChangeCallbacks.erase(it);
            return;
        } else {
            ++it;
        }
    }
}

void pinMode(uint8_t pin, uint8_t mode){
    teensyMockPinMode[pin] = mode;
    updatePinChangeCallbacks(EPinChangeType::eModeChange, pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t val){
    teensyMockPinValues[pin] = val;
    updatePinChangeCallbacks(EPinChangeType::eSet, pin, val);
}

void digitalWriteFast(uint8_t pin, uint8_t val){
    digitalWrite(pin, val);
}

uint8_t digitalRead(uint8_t pin){
    return (uint8_t)teensyMockPinValues[pin];
}

uint8_t digitalReadFast(uint8_t pin){
    return digitalRead(pin);
}

void digitalToggle(uint8_t pin){
    teensyMockPinValues[pin] = !teensyMockPinValues[pin];
    updatePinChangeCallbacks(EPinChangeType::eToggle, pin, teensyMockPinValues[pin]);
}
void digitalToggleFast(uint8_t pin){
    digitalToggle(pin);
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