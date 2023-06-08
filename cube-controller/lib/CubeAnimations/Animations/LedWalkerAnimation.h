/*
 * TestAnimation.h
 *
 * Created: 25.10.2021 19:16:18
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
#include "FrameBuffer.h"

class LedWalkerAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint16_t ledIndex;
        uint32_t cycleCount;
	public:
        LedWalkerAnimation() :
                    FrameGenerator(0),
                    ledIndex(0),
                    cycleCount(0) {
        }
        virtual ~LedWalkerAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            tmpBuffer.clearBuffer();
            ledIndex = 0;
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);

            tmpBuffer.setLed(ledIndex, true);
            tmpBuffer.copyToBuffer(frame);

            setFrameFinished();    
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            ledIndex++;
            if(ledIndex >= TOTAL_LED_COUNT){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};