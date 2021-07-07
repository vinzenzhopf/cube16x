/*
 * CubeFrameBuffer.cpp
 *
 * Created: 01.07.2017 12:27:33
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include <avr/io.h>
#include <string.h>
#include "CubeIO.h"
#include "CubeFrameBuffer.h"

volatile buffer_t buffers[BUFFER_COUNT];
volatile buffer_t *inputBuffer;
volatile buffer_t *outputBuffer;
volatile buffer_t *tmpBuffer;
volatile uint8_t tmpBufferReady;

/************************************************************************/
/* Initializes the data buffers                                         */
/************************************************************************/
void Cube_InitDataBuffer(){
	inputBuffer = buffers;
	tmpBuffer = buffers+1;
	outputBuffer = buffers+2;
	
	tmpBufferReady = 0;
	
	Cube_ClearBuffers();
}

/************************************************************************/
/* Clears the given buffer.                                             */
/************************************************************************/
void Cube_ClearBuffer(volatile buffer_t *pBuffer){
	memset((buffer_t*)pBuffer, 0x00, sizeof(buffer_t));
}

/************************************************************************/
/* Switches the Output-Buffer with the Temp-Buffer.                     */
/************************************************************************/
void Cube_SwitchOutputBuffer(){
	volatile buffer_t *tmp = outputBuffer;
	outputBuffer = tmpBuffer;
	tmpBuffer = tmp;
}

/************************************************************************/
/* Switches the Input-Buffer with the Temp-Buffer.                      */
/************************************************************************/
void Cube_SwitchInputPuffer(){
	volatile buffer_t *tmp = tmpBuffer;
	tmpBuffer = inputBuffer;
	inputBuffer = tmp;
}