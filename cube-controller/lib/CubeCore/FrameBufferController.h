/* 
* FrameBufferController.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#ifndef __FRAMEBUFFERCONTROLLER_H__
#define __FRAMEBUFFERCONTROLLER_H__

#include "FrameBuffer.h"

#define BUFFER_COUNT 3

class FrameBufferController
{
//variables
public:
protected:
    FrameBuffer frameBuffers[BUFFER_COUNT];
    buffer_t *inputBuffer;
	buffer_t *outputBuffer;

    uint8_t inputBufferIdx;
    uint8_t outputBufferIdx;

private:

//functions
public:
	FrameBufferController();
	~FrameBufferController();

    void switchBuffers();
protected:
private:
};

#endif //__FRAMEBUFFERCONTROLLER_H__
