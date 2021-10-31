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
#include "PlaneUtil.h"

#include "Entropy.h"

class FallingLedsAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        int8_t plane[PLANE_LED_COUNT]; 
        uint32_t cycleCount;
        uint32_t currentLed;
        bool fallingMode;
	public:
        FallingLedsAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded) :
                    FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded), 
                    cycleCount(0),
                    currentLed(0),
                    fallingMode(true) {
        }
        virtual ~FallingLedsAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            fallingMode = true;
            memset(&plane, 15, sizeof(int8_t)*256);
            currentLed = Entropy.random(PLANE_LED_COUNT);
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override{
            FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
            cycleCount = 0;
            fallingMode = (frameCounter < 2000);
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            switch(cycleCount){
                case 0:
                    tmpBuffer.clearBuffer();
                    break;
                case 1: 
                    if((fallingMode && plane[currentLed] == 0) || (!fallingMode && plane[currentLed] == 15)){
                        //New index neccessary
                        currentLed = Entropy.random(PLANE_LED_COUNT);
                    }
                    if(fallingMode && plane[currentLed] > 0){
                        //Move Led down
                        plane[currentLed]--;
                    }else if(!fallingMode && plane[currentLed] < 15){
                        //Move led up
                        plane[currentLed]++;
                    }

                    for(uint32_t i = 0; i < PLANE_LED_COUNT; i++){
                        uint16_t index = PLANE_LED_COUNT * plane[i] + i;
                        tmpBuffer.setLed(index, true);
                    }
                    break;
                case 2:  
                    tmpBuffer.copyToBuffer(frame);
                    break;
            }
            cycleCount++;
            if(cycleCount > 1000){
                setFrameFinished();    
            }
        }

        void endFrame(){
            FrameGenerator::endFrame();
            if(frameCounter >= 4000){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};