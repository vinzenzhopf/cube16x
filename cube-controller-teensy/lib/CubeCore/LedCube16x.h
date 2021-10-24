/*
 * LedCube16x.h
 *
 * Defines the frame-buffer and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include <stdint.h>

typedef uint32_t row_t;

#define sbi(port,bit)	(port) |= (1<<(bit))
#define cbi(port,bit)	(port) &= ~(1<<(bit))
#define tbi(port,bit)	(port) ^= (1<<(bit))

#define CUBE_EDGE_SIZE 16

//Define buffer sizes
#define BUFFER_BYTE_SIZE 512
#define BUFFER_SHORT_SIZE (BUFFER_BYTE_SIZE / sizeof(uint16_t)) // 256
#define BUFFER_ROW_SIZE (BUFFER_BYTE_SIZE / sizeof(uint32_t))	// 128

#define PLANE_BYTE_SIZE (BUFFER_BYTE_SIZE / 16)
#define PLANE_SHORT_SIZE (PLANE_BYTE_SIZE / sizeof(uint16_t)) // 16
#define PLANE_ROW_SIZE (PLANE_BYTE_SIZE / sizeof(row_t))	// 8

typedef union {
	uint8_t asBytes[PLANE_BYTE_SIZE];
	uint16_t asShort[PLANE_SHORT_SIZE];
	row_t asRows[PLANE_ROW_SIZE];
} plane_t;

#define PLANE_COUNT (BUFFER_BYTE_SIZE / sizeof(plane_t))

typedef union {
	uint8_t asBytes[BUFFER_BYTE_SIZE];
	uint16_t asShort[BUFFER_SHORT_SIZE];
	row_t asRows[BUFFER_ROW_SIZE];
	plane_t asPlanes[PLANE_COUNT];
} buffer_t;



