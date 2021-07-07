/*
 * CubeFrameBuffer.h
 *
 * Defines the frame-buffers and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */ 
#pragma once

typedef uint8_t char_t;
typedef uint16_t short_t;
typedef uint32_t word_t;

//Define buffer sizes
#define BUFFER_BYTE_SIZE 512
#define BUFFER_SHORT_SIZE (BUFFER_BYTE_SIZE / sizeof(short_t)) // 256
#define BUFFER_WORD_SIZE (BUFFER_BYTE_SIZE / sizeof(word_t))	// 128
#define BUFFER_COUNT 3

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

extern volatile buffer_t *inputBuffer;
extern volatile buffer_t *outputBuffer;
extern volatile buffer_t *tmpBuffer;

extern volatile uint8_t tmpBufferReady;

//Methods

/************************************************************************/
/* Clears the given buffer.                                             */
/************************************************************************/
void Cube_ClearBuffer(volatile buffer_t *pBuffer);

/************************************************************************/
/* Switches the Output-Buffer with the Temp-Buffer.                     */
/************************************************************************/
void Cube_SwitchOutputBuffer();

/************************************************************************/
/* Switches the Input-Buffer with the Temp-Buffer.                      */
/************************************************************************/
void Cube_SwitchInputPuffer();

/************************************************************************/
/* Initializes the data buffers.                                        */
/************************************************************************/
void Cube_InitDataBuffer();

/************************************************************************/
/* Clears all Buffers.                                                  */
/************************************************************************/
inline void Cube_ClearBuffers(){
	Cube_ClearBuffer(outputBuffer);
	Cube_ClearBuffer(tmpBuffer);
	Cube_ClearBuffer(inputBuffer);
}

/************************************************************************/
/* Rotates the Buffer-Pointers.                                         */
/* Note: Check first, if the Buffer is Ready!                           */
/************************************************************************/
inline void Cube_RotateBuffers(){
	Cube_SwitchOutputBuffer();
	Cube_SwitchInputPuffer();
}

/************************************************************************/
/* Checks if the Temporary Buffer is ready to rotate.                   */
/************************************************************************/
inline uint8_t Cube_IsTmpBufferReady() {
	return tmpBufferReady;
}