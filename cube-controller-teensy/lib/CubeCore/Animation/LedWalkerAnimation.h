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

class LedWalkerAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint16_t ledIndex;
        uint32_t cycleCount;
	public:
        LedWalkerAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded) :
                    FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded),
                    ledIndex(0),
                    cycleCount(0) {
        }
        virtual ~LedWalkerAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            tmpBuffer.clearBuffer();
            ledIndex = 0;
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override{
            FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);

            tmpBuffer.setLed(ledIndex, true);
            tmpBuffer.copyToBuffer(frame);

            cycleCount++;
            if(cycleCount > 1000){
                setFrameFinished();    
            }
        }

        void endFrame(){
            FrameGenerator::endFrame();
            ledIndex++;
            if(ledIndex >= TOTAL_LED_COUNT){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};