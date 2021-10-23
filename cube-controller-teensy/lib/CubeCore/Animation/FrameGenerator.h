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
    protected:
        buffer_t *nextFrame;

        uint32_t totalFrameTimeUs;
        uint32_t frameCounter;

        uint32_t sequenceStartTicks;
        uint32_t lastFrameStartTicks;
    private:
        bool frameFinished;
        bool sequenceFinished;

	public:
        FrameGenerator(){
        }
        ~FrameGenerator(){
        }

        void restartFrameSequence(uint32_t currentTicks){
            this->sequenceStartTicks = currentTicks;
            this->sequenceFinished = false;
            initializeFrameSequence();
        }

        void startNewFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs){
            this->nextFrame = nextFrame;
            this->frameFinished = false;

            this->lastFrameStartTicks = currentTicks;
            this->totalFrameTimeUs = totalFrameTimeUs;
            initializeFrame();
        }

        virtual void generateCyclic(uint32_t const currentTicks) = 0;

        bool isSequenceFinished(){
            return sequenceFinished;
        }

        bool isFrameFinished(){
            return frameFinished;
        }
        bool getFrameCounter(){
            return frameCounter;
        }

    protected:
        virtual void initializeFrameSequence() = 0;
        virtual void initializeFrame() = 0;

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