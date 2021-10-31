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
        uint32_t const frameTimeUs;
        
    protected:
        buffer_t *frame;

        //uint32_t animationDurationMs;
        uint32_t frameCounter;

        uint32_t sequenceStartTicks;
        uint32_t frameStartTicks;
        
    private:
        bool frameFinished;
        bool sequenceFinished;

	public:
        FrameGenerator();
        FrameGenerator(uint32_t const frameTimeUs);
        virtual ~FrameGenerator() = default;

        virtual void initializeFrameSequence(uint32_t currentTicks) override;
        virtual void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override;
        virtual void generateCyclicBase(uint32_t const currentTicks) override;
        virtual void endFrame(uint32_t const currentTicks) override;

        bool isSequenceFinished() override;
        bool isFrameFinished() override;
        uint32_t getFrameCounter() override;

        uint32_t getFrameTimeUs() override{
            return frameTimeUs;
        }
        bool isFreeRunning() override{
            return frameTimeUs == 0;
        }

        uint32_t inline getElapsedSequenceTime(uint32_t const currentTicks){
            return currentTicks - sequenceStartTicks;
        }
        uint32_t inline getElapsedFrameTime(uint32_t const currentTicks){
            return currentTicks - frameStartTicks;
        }
        uint32_t inline getRemainingFrameTime(uint32_t const currentTicks){
            return frameTimeUs - getElapsedFrameTime(currentTicks);
        }

        void setFrameStartTicks(uint32_t const startTicks) override{
            frameStartTicks = startTicks;
        }
    protected:
        void inline setSequenceFinished(){
            sequenceFinished = true;
        }

        void inline setFrameFinished(){
            frameFinished = true;
        }
    private:  
};

