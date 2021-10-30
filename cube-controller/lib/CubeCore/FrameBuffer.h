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
#include <string.h>
#include <math.h>

#include "BufferUtil.h"

class FrameBuffer final : public BufferUtil {
    public:
    protected:
        buffer_t buffer;
    private:
	public:
        FrameBuffer() : BufferUtil(&buffer){
        }
        ~FrameBuffer() = default;

        void resetBufferRef(){
            updateBufferRef(&buffer);
        }

    private:
};

