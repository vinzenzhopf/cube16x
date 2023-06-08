        

#include "InputHandler.h"

void InputHandlerOnHIDKeyExtrasPress(uint32_t top, uint16_t key) {
    InputHandler.KeyboardOnExtrasPressInternal(top, key);
}

void InputHandlerOnHIDKeyExtrasRelease(uint32_t top, uint16_t key) {
    InputHandler.KeyboardOnExtrasReleaseInternal(top, key);
}

void InputHandlerOnHIDKeyPress(int unicode) {
    InputHandler.KeyboardOnPressInternal(unicode);
}

void InputHandlerOnHIDKeyRelease(int unicode) {
    InputHandler.KeyboardOnReleaseInternal(unicode);
}

InputHandlerClass::InputHandlerClass() :
    myusb(),
    hub1(myusb),
    keyboard1(myusb) {
}

void InputHandlerClass::setup(){
    myusb.begin();

    keyboard1.attachPress(InputHandlerOnHIDKeyPress);
    keyboard1.attachRelease(InputHandlerOnHIDKeyRelease);
    keyboard1.attachExtrasPress(InputHandlerOnHIDKeyExtrasPress);
    keyboard1.attachExtrasRelease(InputHandlerOnHIDKeyExtrasRelease);
}

void InputHandlerClass::loop(){
    myusb.Task();
}

void InputHandlerClass::KeyboardOnPressInternal(uint16_t unicode){
    uint8_t modifier = keyboard1.getModifiers();
    uint8_t key = keyboard1.getOemKey();
    for(auto it = keyCallbacks.begin(); it != keyCallbacks.end(); ++it) {
        if(*it){
            (*it)->OnRawPress(modifier, unicode, key);
        }
    }
}
void InputHandlerClass::KeyboardOnReleaseInternal(uint16_t unicode){
    uint8_t modifier = keyboard1.getModifiers();
    uint8_t key = keyboard1.getOemKey();
    for(auto it = keyCallbacks.begin(); it != keyCallbacks.end(); ++it) {
        if(*it){
            (*it)->OnRawRelease(modifier, unicode, key);
        }
    }
}
void InputHandlerClass::KeyboardOnExtrasPressInternal(uint32_t top, uint16_t key){
    for(auto it = keyCallbacks.begin(); it != keyCallbacks.end(); ++it) {
        if(*it){
            (*it)->OnExtrasPress(top, key);
        }
    }
}
void InputHandlerClass::KeyboardOnExtrasReleaseInternal(uint32_t top, uint16_t key){
    for(auto it = keyCallbacks.begin(); it != keyCallbacks.end(); ++it) {
        if(*it){
            (*it)->OnExtrasRelease(top, key);
        }
    }
}

void InputHandlerClass::AddKeyCallback(IHIDKeyCallback *callback){
    keyCallbacks.push_back(callback);
}

bool InputHandlerClass::removeKeyCallback(IHIDKeyCallback *callback){
    for (auto it = keyCallbacks.begin(); it != keyCallbacks.end(); ++it) {
    {
        if (*it && *it == callback)
        {
            keyCallbacks.erase(it);
            return true;
        }
    }
    return false;
}
