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

class TestAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint8_t ledIndex;
        uint32_t cycleCount;
	public:
        TestAnimation() :
                    FrameGenerator(200000),
                    ledIndex(0),
                    cycleCount(0) {
        }
        virtual ~TestAnimation() = default;

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

            cycleCount++;
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