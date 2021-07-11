/* 
* FrameBufferController.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "FrameBufferController.h"


FrameBufferController::FrameBufferController()
{
    nFrontBufferIdx = 0;
    nBackBufferIdx = 1;
}

FrameBufferController::~FrameBufferController()
{
}

void FrameBufferController::switchBuffers(){
    uint8_t tmp = nBackBufferIdx;
    nBackBufferIdx = nFrontBufferIdx;
    nFrontBufferIdx = tmp;
    bBackBufferReady = false;
    bFrontBufferReady = false;
}

bool FrameBufferController::initialize(){
    bool tmp = CyclicModule::initialize();
    arrFrameBuffers[0].clearBuffer();
    arrFrameBuffers[1].clearBuffer();
    bBackBufferReady = true;
    bFrontBufferReady = false;
    return tmp;
}

void FrameBufferController::cyclic(){
    CyclicModule::cyclic();
}

bool FrameBufferController::isFrontBufferReady(){
    return bFrontBufferReady;
}

void FrameBufferController::setFrontBufferReady(bool value){
    bFrontBufferReady = value;
}

bool FrameBufferController::isBackBufferReady(){
    return bBackBufferReady;
}

void FrameBufferController::setBackBufferReady(bool value){
    bBackBufferReady = value;
}
    
buffer_t* FrameBufferController::getFrontBuffer(){
    return arrFrameBuffers[nFrontBufferIdx].getBuffer();
}

buffer_t* FrameBufferController::getBackBuffer(){
    return arrFrameBuffers[nBackBufferIdx].getBuffer();
}

void FrameBufferController::copyBuffer(buffer_t *pBuffer){
    arrFrameBuffers[nBackBufferIdx].copyBuffer(pBuffer);
} 