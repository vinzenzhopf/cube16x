/*
 * TeensyMock.h
 *
 * Created: 24.10.2021 09:54:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#ifdef PLATFORM_NATIVE

#define TEENSY_PIN_COUNT 54

#include <stdint.h>
#include <chrono>
#include "IPinChangeCallback.h"

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

void addPinChangeCallback(IPinChangeCallback *callback);
void removePinChangeCallback(IPinChangeCallback *callback);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
void digitalWriteFast(uint8_t pin, uint8_t val);
uint8_t digitalRead(uint8_t pin);
uint8_t digitalReadFast(uint8_t pin);
void digitalToggle(uint8_t pin);
void digitalToggleFast(uint8_t pin);

uint32_t millis();
uint32_t micros();

#endif