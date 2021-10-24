/*
 * CubeCore.h
 *
 * Base Include file for all general references of the CubeCore lib.
 *
 *
 * Created: 21.10.2021 22:27:57
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#ifndef PLATFORM_NATIVE
#include <Arduino.h>
#else
#include "NativeArduinoMock.h"
#endif

#include "LedCube16x.h"

#define MAX_MODULE_COUNT 10
#define MAX_PLAYLIST_ENTRIES 16



