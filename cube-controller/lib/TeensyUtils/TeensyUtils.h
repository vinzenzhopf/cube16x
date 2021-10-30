/*
 * TeensyUtils.h
 *
 * Aggregations of useful functions to use with the Teensy-Adurino API
 */ 

#pragma once

#include <stdint.h>

#ifndef PLATFORM_NATIVE
#include <Arduino.h>
#else
#include "NativeArduinoMock.h"
#endif

#define NOP1 "nop\n\t"
#define NOP2 "nop\n\t""nop\n\t"
#define NOP3 "nop\n\t""nop\n\t""nop\n\t"
#define NOP4 "nop\n\t""nop\n\t""nop\n\t""nop\n\t"

#define NOP_DELAY4 __asm__(NOP4)
#define NOP_DELAY8 __asm__(NOP4 NOP4)
#define NOP_DELAY16 __asm__(NOP4 NOP4 NOP4 NOP4)

inline void digitalWriteByte(uint8_t startPin, uint8_t byte){
    for(int i = 0; i < 8; i++){
        digitalWriteFast(startPin+i, (byte&(1<<i))!=0);
    }
}

inline uint8_t digitalReadByte(uint8_t startPin){
    uint8_t byte = 0;
    for(int i = 0; i < 8; i++){
        byte |= (digitalReadFast(startPin+i)<<i);
    }
    return byte;
}



