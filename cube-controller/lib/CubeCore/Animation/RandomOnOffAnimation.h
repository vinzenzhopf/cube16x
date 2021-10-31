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

class RandomOnOffAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        uint32_t currentLed;
        bool turnOffPhase;
	public:
        RandomOnOffAnimation() :
                    FrameGenerator(), 
                    cycleCount(0),
                    currentLed(0),
                    turnOffPhase(false) {
        }
        virtual ~RandomOnOffAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            tmpBuffer.clearBuffer();
            turnOffPhase = false;
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
            if(frameCounter >= 3000){
                turnOffPhase = true;
            }
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            for(uint8_t i = 0; i < 20; i++){
                currentLed = Entropy.random(4096);
                tmpBuffer.setLed(currentLed, !turnOffPhase);
            }
            tmpBuffer.copyToBuffer(frame);
            setFrameFinished();
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(frameCounter >= 6000){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};