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

#include <LedCube16x.h>

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