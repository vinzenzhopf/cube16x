
#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
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
        RandomToggleAnimation() :
                    FrameGenerator(50), 
                    currentLed(0) {
        }
        virtual ~RandomToggleAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            tmpBuffer.clearBuffer();
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
        }

        bool generateCyclicBase(uint32_t const currentTicks){
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
                    return true; 
                    break;
            }
            cycleCount++;
            return false;
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(frameCounter >= 8000){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};