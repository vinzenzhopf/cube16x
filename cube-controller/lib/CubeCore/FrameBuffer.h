/*
 * FrameBuffer.h
 *
 * Defines the frame-buffer and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <avr/io.h>

typedef uint8_t char_t;
typedef uint16_t short_t;
typedef uint32_t word_t;

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

class FrameBuffer {
    public:
    protected:
        buffer_t buffer;
    private:
	
	public:
		/************************************************************************/
		/* Clears the given buffer.                                             */
		/************************************************************************/
		void clearBuffer();
    
        /************************************************************************/
		/* Returns a pointer to the buffer.                                     */
		/************************************************************************/
        buffer_t* getBuffer();

    protected:
    private:
};

#endif //__FRAMEBUFFER_H__