/* 
* FrameBufferController.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "FrameBufferController.h"


FrameBufferController::FrameBufferController()
{
    inputBufferIdx = 0;
    outputBufferIdx = 1;
    inputBuffer = frameBuffers[inputBufferIdx].getBuffer();
    outputBuffer = frameBuffers[outputBufferIdx].getBuffer();
}

FrameBufferController::~FrameBufferController()
{
}

void FrameBufferController::switchBuffers(){
    uint8_t tmp = inputBufferIdx;
    outputBufferIdx = inputBufferIdx;
    inputBufferIdx = tmp;
    inputBuffer = frameBuffers[inputBufferIdx].getBuffer();
    outputBuffer = frameBuffers[outputBufferIdx].getBuffer();
}

