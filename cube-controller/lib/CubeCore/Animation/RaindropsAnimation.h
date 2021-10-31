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

class RaindropsAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        int8_t plane[PLANE_LED_COUNT]; 
        plane_t floor;
        uint32_t cycleCount;
        uint32_t currentLed;
	public:
        RaindropsAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded) :
                    FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded), 
                    currentLed(0) {
        }
        virtual ~RaindropsAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            memset(&plane, 0, sizeof(int8_t)*256);
            memset(&floor, 0, sizeof(plane_t));
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override{
            FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            switch(cycleCount){
                case 0:
                    tmpBuffer.clearBuffer();
                    break;
                case 1: 
                    //4 new Drops per run
                    for(uint32_t i = 0; i < 8; i++){
                        uint32_t newDropIdx = Entropy.random(PLANE_LED_COUNT);
                        if(plane[newDropIdx] == 0)
                            plane[newDropIdx] = 16;
                    }

                    //Advance every "drop" by one
                    for(uint32_t i = 0; i < PLANE_LED_COUNT; i++){
                        if(plane[i] == 1){
                            //write wet floor
                            PlaneUtil.setLed(&floor, i, true);
                        }
                        if(plane[i] > 0){
                            plane[i]--;
                        }
                    }
                    break;
                case 2:
                    //Write all drops
                    for(uint32_t i = 0; i < PLANE_LED_COUNT; i++){
                        if(plane[i] > 0){
                            uint16_t index = PLANE_LED_COUNT * plane[i] + i;
                            tmpBuffer.setLed(index, true);
                        }
                    }
                    
                    //write wet floor   
                    tmpBuffer.setPlane(0, &floor);
                    break;
                case 3:  
                    tmpBuffer.copyToBuffer(frame);
                    break;
            }
            cycleCount++;
            if(cycleCount > 3000){
                setFrameFinished();    
            }
        }

        void endFrame(){
            FrameGenerator::endFrame();
            if(frameCounter >= 800){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};