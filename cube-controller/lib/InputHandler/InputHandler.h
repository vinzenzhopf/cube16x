


#pragma once

#include "Arduino.h"
#include "USBHost_t36.h"
#include "vector"

#include "IHIDKeyCallback.h"

class InputHandlerClass final{
    public:
        USBHost myusb;
        USBHub hub1;
        KeyboardController keyboard1;
    protected:
        std::vector<IHIDKeyCallback*> keyCallbacks;
    private:
    public:
        InputHandlerClass();
        ~InputHandlerClass() = default;

        void setup();
        void loop();

        void KeyboardOnPressInternal(uint16_t unicode);
        void KeyboardOnReleaseInternal(uint16_t unicode);
        void KeyboardOnExtrasPressInternal(uint32_t top, uint16_t key);
        void KeyboardOnExtrasReleaseInternal(uint32_t top, uint16_t key);

        void AddKeyCallback(IHIDKeyCallback *callback);
        bool removeKeyCallback(IHIDKeyCallback *callback);
    protected:
    private:
};
extern InputHandlerClass InputHandler;