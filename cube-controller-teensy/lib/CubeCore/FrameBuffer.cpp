/*
 * CubeFrameBuffer.cpp
 *
 * Created: 01.07.2017 12:27:33
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include "FrameBuffer.h"

/**
 * Clears the buffer.
 */
void FrameBuffer::clearBuffer(){
	//memset(&buffer, 0x00, sizeof(buffer_t)); //doesnt work?? dunno
	this->setBufferToByte(0x00);
}

/**
 * Sets the buffer to all 1.
 */
void FrameBuffer::setBuffer(){
	//memset((buffer_t*)&buffer, 0xFF, sizeof(buffer_t)); //doesnt work?? dunno
	this->setBufferToByte(0xFF);
}

void FrameBuffer::setBufferToByte(uint8_t byte){
	for(uint16_t i = 0; i < BUFFER_BYTE_SIZE; i++){
		buffer.asBytes[i] = byte;
	}
}

/**
 * Sets the Buffer to an alternating pattern, where each bit is alternating zu the prevoius.
 */
void FrameBuffer::setBufferAlternating(){
    for(uint8_t i = 0; i < PLANE_COUNT; i++){
        for(uint8_t j = 0; j < PLANE_SHORT_SIZE; j++){
            buffer.asPlanes[i].asShort[j] = (j%2==0)?0b1010101010101010:0b0101010101010101;
        }
    }
}

/**
 * Returns a pointer to the buffer.
 */
buffer_t* FrameBuffer::getBuffer(){
    return &buffer;
}