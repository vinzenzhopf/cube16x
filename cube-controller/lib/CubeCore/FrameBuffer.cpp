/*
 * CubeFrameBuffer.cpp
 *
 * Created: 01.07.2017 12:27:33
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include <avr/io.h>
#include <string.h>
#include "FrameBuffer.h"

/************************************************************************/
/* Clears the given buffer.                                             */
/************************************************************************/
void FrameBuffer::clearBuffer(){
	memset((buffer_t*)&buffer, 0x00, sizeof(buffer_t));
}

/************************************************************************/
/* Returns a pointer to the buffer.                                     */
/************************************************************************/
buffer_t* FrameBuffer::getBuffer(){
    return &buffer;
}