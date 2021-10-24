/*
 * FrameGenerator.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#ifndef __FRAMEGENERATOR_H__
#define __FRAMEGENERATOR_H__

#include "CubeCore.h"

class FrameGenerator {
    public:
        uint32_t const animationFrameTimeUs;
        bool const repeatUntilTimeExeeded;

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
                        bool const repeatUntilTimeExeeded);
        virtual ~FrameGenerator() = default;

        virtual void restartFrameSequence(uint32_t currentTicks);
        virtual void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs);
        virtual void generateCyclicBase(uint32_t const currentTicks);

        void endFrame();

        bool isSequenceFinished();

        bool isFrameFinished();
        bool getFrameCounter();

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

#endif //__FRAMEGENERATOR_H__