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
        virtual void startFrame(buffer_t *nextFrame, uint32_t currentTicks) = 0;
        virtual bool generateCyclicBase(uint32_t currentTicks) = 0;
        virtual void endFrame(uint32_t currentTicks) = 0;
        
        virtual bool isSequenceFinished() = 0;
        virtual bool isFrameFinished() = 0;
        virtual void setFrameFinished() = 0;
        
        virtual uint32_t getFrameCounter() = 0;

        virtual uint32_t getFrameTimeUs() = 0;
        virtual bool isFreeRunning() = 0;

        virtual void setFrameStartTicks(uint32_t const startTicks) = 0;

        virtual uint32_t getElapsedSequenceTime(uint32_t const currentTicks) = 0;
        virtual uint32_t getElapsedFrameTime(uint32_t const currentTicks) = 0;
        virtual uint32_t getRemainingFrameTime(uint32_t const currentTicks) = 0;
};

