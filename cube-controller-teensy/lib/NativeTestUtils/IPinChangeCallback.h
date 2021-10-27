
#pragma once

#include <stdint.h>

enum class EPinChangeType : uint8_t {
    eSet,
    eToggle,
    eModeChange
};

class IPinChangeCallback {
    public:
        virtual void pinChange(EPinChangeType type, uint8_t pin, uint8_t val) = 0;
};