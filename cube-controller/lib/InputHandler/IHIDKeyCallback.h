
#pragma once

#include <stdint.h>

class IHIDKeyCallback {
    public:
        void OnRawPress(uint8_t modifier, uint16_t unicode, uint16_t key);
        void OnRawRelease(uint8_t modifier, uint16_t unicode, uint16_t key);
        void OnExtrasPress(uint32_t top, uint16_t key);
        void OnExtrasRelease(uint32_t top, uint16_t key);
};