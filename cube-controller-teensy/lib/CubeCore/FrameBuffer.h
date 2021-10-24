/*
 * FrameBuffer.h
 *
 * Defines the frame-buffer and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include <LedCube16x.h>

class FrameBuffer {
    public:
    protected:
        buffer_t buffer;
    private:
	
	public:
		/**
         * Clears the buffer.
         */
		void clearBuffer();
    
        /**
         * Sets the buffer to all 1.
         */
        void setBuffer();

        /**
		 * Returns a pointer to the buffer.
		 */
        buffer_t* getBuffer();

        /**
         * Sets the Buffer to an alternating pattern, where each bit is alternating zu the prevoius.
         */
        void setBufferAlternating();

        /**
         * Copys the given buffer to this buffer.
         */        
        void copyFromBuffer(buffer_t *pBuffer){
            for(uint16_t i = 0; i < BUFFER_ROW_SIZE; i++){
                buffer.asRows[i] = pBuffer->asRows[i];
            }
        } 

        /**
         * Copys the this buffer to the given buffer.
         */        
        void copyToBuffer(buffer_t *pBuffer){
            for(uint16_t i = 0; i < BUFFER_ROW_SIZE; i++){
                pBuffer->asRows[i] = buffer.asRows[i];
            }
        } 

    protected:
        void setBufferToByte(uint8_t byte);
    private:
};

