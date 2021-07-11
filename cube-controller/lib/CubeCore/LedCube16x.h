/*
 * LedCube16x.h
 *
 * Defines the frame-buffer and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __LEDCUBE16X_H__
#define __LEDCUBE16X_H__

#include <avr/io.h>

typedef uint8_t char_t;
typedef uint16_t short_t;
typedef uint32_t word_t;

#define sbi(port,bit)	(port) |= (1<<(bit))
#define cbi(port,bit)	(port) &= ~(1<<(bit))
#define tbi(port,bit)	(port) ^= (1<<(bit))

#define CUBE_EDGE_SIZE 16

//Define buffer sizes
#define BUFFER_BYTE_SIZE 512
#define BUFFER_SHORT_SIZE (BUFFER_BYTE_SIZE / sizeof(short_t)) // 256
#define BUFFER_WORD_SIZE (BUFFER_BYTE_SIZE / sizeof(word_t))	// 128

#define PLANE_BYTE_SIZE (BUFFER_BYTE_SIZE / 16)
#define PLANE_SHORT_SIZE (PLANE_BYTE_SIZE / sizeof(short_t)) // 16
#define PLANE_WORD_SIZE (PLANE_BYTE_SIZE / sizeof(word_t))	// 8

typedef union {
	char_t asBytes[PLANE_BYTE_SIZE];
	short_t asShort[PLANE_SHORT_SIZE];
	word_t asWords[PLANE_WORD_SIZE];
} plane_t;

#define PLANE_COUNT (BUFFER_BYTE_SIZE / sizeof(plane_t))

typedef union {
	char_t asBytes[BUFFER_BYTE_SIZE];
	short_t asShort[BUFFER_SHORT_SIZE];
	word_t asWords[BUFFER_WORD_SIZE];
	plane_t asPlanes[PLANE_COUNT];
} buffer_t;

#endif //__LEDCUBE16X_H__

