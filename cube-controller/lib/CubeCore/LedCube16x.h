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

#define sbi(port,bit)	(port) |= (1<<(bit))
#define cbi(port,bit)	(port) &= ~(1<<(bit))
#define tbi(port,bit)	(port) ^= (1<<(bit))

typedef uint8_t	byte_t;
typedef uint16_t row_t;
typedef uint32_t word_t;

const uint8_t 	CUBE_EDGE_SIZE 		= 16;
const uint16_t	PLANE_LED_COUNT 	= CUBE_EDGE_SIZE * CUBE_EDGE_SIZE; // 256
const uint16_t	TOTAL_LED_COUNT 	= CUBE_EDGE_SIZE * CUBE_EDGE_SIZE * CUBE_EDGE_SIZE; // 4096
const uint8_t	PLANE_COUNT 		= CUBE_EDGE_SIZE; // 16

const uint8_t	LEDS_PER_BYTE		= 8;

//Define plane sizes
const int		PLANE_BYTE_SIZE 	= PLANE_LED_COUNT / LEDS_PER_BYTE;		// 32
const int		PLANE_ROW_SIZE 		= PLANE_BYTE_SIZE / sizeof(row_t);		// 16
const int		PLANE_WORD_SIZE 	= PLANE_BYTE_SIZE / sizeof(word_t);		// 8

typedef union {
	uint8_t asBytes[PLANE_BYTE_SIZE];
	row_t asRows[PLANE_ROW_SIZE];
	word_t asWords[PLANE_WORD_SIZE];
} plane_t;

const int 		LEDS_PER_ROW		= sizeof(row_t) * LEDS_PER_BYTE; 
const int 		LEDS_PER_WORD		= sizeof(word_t) * LEDS_PER_BYTE;
const int 		LEDS_PER_PLANE		= sizeof(plane_t) * LEDS_PER_BYTE;

//Define buffer sizes
const int		BUFFER_BYTE_SIZE	= TOTAL_LED_COUNT / LEDS_PER_BYTE;		// 512
const int		BUFFER_ROW_SIZE		= BUFFER_BYTE_SIZE / sizeof(row_t); 	// 256
const int		BUFFER_WORD_SIZE	= BUFFER_BYTE_SIZE / sizeof(word_t);	// 128
const int		BUFFER_PLANE_COUNT	= BUFFER_BYTE_SIZE / sizeof(plane_t);	// 16

typedef union {
	uint8_t asBytes[BUFFER_BYTE_SIZE];
	row_t asRows[BUFFER_ROW_SIZE];
	word_t asWords[BUFFER_WORD_SIZE];
	plane_t asPlanes[PLANE_COUNT];
} buffer_t;

//Parameter for the hardware connection:
//Number of LED per Shift-Register Stack
const int		SHIFT_REGISTER_LANE_COUNT = 8;
const int 		SHIFT_REGISTER_DEPTH = PLANE_LED_COUNT / SHIFT_REGISTER_LANE_COUNT;
const int		SHIFT_REGISTER_DEPTH_BYTES = SHIFT_REGISTER_DEPTH / 8;

enum class ECubeDirection :  uint8_t {
	X, //Front
	Y, //Side/Right
	Z, //Up
};
