/*
 * ICyclicFrameGeneration.h
 *
 * Created: 10.07.2017 16:31
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"

class ICyclicFrameGeneration
{
    public:
        virtual void initializeFrameSequence(uint32_t currentTicks) = 0;
        virtual void startFrame(buffer_t *nextFrame, uint32_t currentTicks, uint32_t totalFrameTimeUs) = 0;
        virtual void generateCyclicBase(uint32_t currentTicks) = 0;
        virtual void endFrame() = 0;
        
        virtual bool isSequenceFinished() = 0;
        virtual bool isFrameFinished() = 0;
        virtual uint32_t getFrameCounter() = 0;

        virtual uint32_t getAnimationFrameTimeUs() = 0;
        virtual bool getRepeatUntilTimeExceeded() = 0;
};

