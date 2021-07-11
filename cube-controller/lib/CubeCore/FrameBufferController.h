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

class FrameBufferController : public CyclicModule
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
	FrameBufferController();
	~FrameBufferController();

    void switchBuffers();
    bool isFrontBufferReady();
    void setFrontBufferReady(bool value);
    bool isBackBufferReady();
    void setBackBufferReady(bool value);
    buffer_t* getFrontBuffer();
    buffer_t* getBackBuffer();
    void copyBuffer(buffer_t *pBuffer); 

    bool initialize() override;
    void cyclic() override;
protected:
private:
};

#endif //__FRAMEBUFFERCONTROLLER_H__
