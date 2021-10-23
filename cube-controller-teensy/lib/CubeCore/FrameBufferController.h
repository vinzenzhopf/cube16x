/* 
* FrameBufferController.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#ifndef __FRAMEBUFFERCONTROLLER_H__
#define __FRAMEBUFFERCONTROLLER_H__

#include "FrameBuffer.h"
#include "Base/CyclicModule.h"

#define BUFFER_COUNT 2

class FrameBufferController final : public CyclicModule
{
//variables
public:
protected:
    FrameBuffer arrFrameBuffers[BUFFER_COUNT];
    uint8_t nFrontBufferIdx;
    uint8_t nBackBufferIdx;

    bool bBackBufferReady;
    bool bFrontBufferReady;
private:

//functions
public:
	FrameBufferController()
    {
        nFrontBufferIdx = 0;
        nBackBufferIdx = 1;
    }

	~FrameBufferController()
    {
    }

    void switchBuffers(){
        uint8_t tmp = nBackBufferIdx;
        nBackBufferIdx = nFrontBufferIdx;
        nFrontBufferIdx = tmp;
        bBackBufferReady = false;
        bFrontBufferReady = false;
    }

    bool isFrontBufferReady(){
        return bFrontBufferReady;
    }
    void setFrontBufferReady(){
        bFrontBufferReady = true;
    }
    bool isBackBufferReady(){
        return bBackBufferReady;
    }
    void setBackBufferReady(){
        bBackBufferReady = true;
    }
    buffer_t* getFrontBuffer(){
        return arrFrameBuffers[nFrontBufferIdx].getBuffer();
    }
    buffer_t* getBackBuffer(){
        return arrFrameBuffers[nBackBufferIdx].getBuffer();
    }

    void copyBuffer(buffer_t *pBuffer){
        arrFrameBuffers[nBackBufferIdx].copyBuffer(pBuffer);
    } 

    bool initialize(){
        arrFrameBuffers[0].clearBuffer();
        arrFrameBuffers[1].clearBuffer();
        bBackBufferReady = true;
        bFrontBufferReady = false;
        return true;
    }

    void cyclic(){
    }
    
protected:
private:
};

#endif //__FRAMEBUFFERCONTROLLER_H__
