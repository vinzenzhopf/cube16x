/*
 * FrameGenerator.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "ICyclicFrameGeneration.h"

class FrameGenerator : public ICyclicFrameGeneration {
    public:
        uint32_t const animationFrameTimeUs;
        bool const repeatUntilTimeExceeded;

    protected:
        buffer_t *frame;

        uint32_t totalFrameTimeUs;
        uint32_t frameCounter;

        uint32_t sequenceStartTicks;
        uint32_t lastFrameStartTicks;
    private:
        bool frameFinished;
        bool sequenceFinished;

	public:
        FrameGenerator( uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExceeded);
        virtual ~FrameGenerator() = default;

        virtual void initializeFrameSequence(uint32_t currentTicks) override;
        virtual void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override;
        virtual void generateCyclicBase(uint32_t const currentTicks) override;
        virtual void endFrame() override;

        bool isSequenceFinished() override;
        bool isFrameFinished() override;
        uint32_t getFrameCounter() override;

        bool getAnimationFrameTimeUs() override{
            return animationFrameTimeUs;
        }
        bool getRepeatUntilTimeExceeded() override{
            return repeatUntilTimeExceeded;
        }

    protected:
        void inline setSequenceFinished(){
            sequenceFinished = true;
        }

        void inline setFrameFinished(){
            frameFinished = true;
        }

        uint32_t inline getElapsedSequenceTime(uint32_t const currentTicks){
            return currentTicks - lastFrameStartTicks;
        }
        uint32_t inline getElapsedFrameTime(uint32_t const currentTicks){
            return currentTicks - lastFrameStartTicks;
        }
        uint32_t inline getRemainingFrameTime(uint32_t const currentTicks){
            return totalFrameTimeUs - getElapsedFrameTime(currentTicks);
        }
    private:  
};

