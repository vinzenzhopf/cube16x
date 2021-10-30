/*
 * TestAnimation.h
 *
 * Created: 25.10.2021 19:16:18
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "FrameGenerator.h"
#include "FrameBuffer.h"

#include "Entropy.h"

class RandomToggleAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        uint32_t currentLed;
	public:
        RandomToggleAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded) :
                    FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded), 
                    currentLed(0) {
        }
        virtual ~RandomToggleAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            tmpBuffer.clearBuffer();
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override{
            FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            uint8_t value;
            switch(cycleCount){
                case 0:
                    currentLed = Entropy.random(4096);
                    break;
                case 1: 
                    value = !tmpBuffer.getLed(currentLed);
                    tmpBuffer.setLed(currentLed, value);
                    break;
                case 2:  
                    tmpBuffer.copyToBuffer(frame);
                    break;
            }
            cycleCount++;
            if(cycleCount > 50){
                setFrameFinished();    
            }
        }

        void endFrame(){
            FrameGenerator::endFrame();
            if(frameCounter >= 8000){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};