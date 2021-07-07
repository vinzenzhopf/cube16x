/* 
* FrameBufferController.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#ifndef __FRAMEBUFFERCONTROLLER_H__
#define __FRAMEBUFFERCONTROLLER_H__


class FrameBufferController
{
//variables
public:
	extern volatile buffer_t *inputBuffer;
	extern volatile buffer_t *outputBuffer;
	extern volatile buffer_t *tmpBuffer;

	extern volatile uint8_t tmpBufferReady;
protected:
private:

//functions
public:
	FrameBufferController();
	~FrameBufferController();
protected:
private:
	FrameBufferController( const FrameBufferController &c );
	FrameBufferController& operator=( const FrameBufferController &c );

}; //FrameBufferController

#endif //__FRAMEBUFFERCONTROLLER_H__
