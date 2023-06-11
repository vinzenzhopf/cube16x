
#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
#include "FrameBuffer.h"
#include "Util/PlaneUtil.h"

#include "Entropy.h"

class RaindropsAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        int8_t plane[PLANE_LED_COUNT]; 
        plane_t floor;
        uint32_t currentLed;
	public:
        RaindropsAnimation() :
                    FrameGenerator(20000), 
                    cycleCount(0),
                    currentLed(0) {
        }
        virtual ~RaindropsAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            memset(&plane, 0, sizeof(int8_t)*256);
            memset(&floor, 0, sizeof(plane_t));
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
        }

        bool generateCyclicBase(uint32_t const currentTicks){
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
                case 4:
                    return true;
                    break;
            }
            cycleCount++;
            return false;
        }

        void endFrame(uint32_t currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(frameCounter >= 800){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};