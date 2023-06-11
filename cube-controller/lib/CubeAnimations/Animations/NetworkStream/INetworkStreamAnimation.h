/*
 * INetworkStreamAnimation.h
 *
 * Created: 11.06.2023 15:54
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"

class INetworkStreamAnimation
{
    public:
        virtual void startAnimation(uint32_t targetFrameTimeUs) = 0;
        virtual void endAnimation() = 0;
        virtual void updateFrame(buffer_t *nextFrame, uint32_t targetFrameTimeUs) = 0;
        virtual uint32_t lastFrameTimeUs() = 0;
};

