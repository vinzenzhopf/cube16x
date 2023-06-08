/*
 * PlaneWalkerAnimation.h
 *
 * Created: 24.10.2021 23:14:23
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
#include "FrameBuffer.h"

class PlaneWalkerAnimation2 : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        uint8_t planeIndex;
        uint8_t state;
	public:
        PlaneWalkerAnimation2() :
                    FrameGenerator(10000),
                    cycleCount(0),
                    planeIndex(0),
                    state(0) {
        }
        virtual ~PlaneWalkerAnimation2() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            planeIndex = 0;
            state = 0;
            tmpBuffer.clearBuffer();
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);

            switch(cycleCount){
                case 0:
                    tmpBuffer.clearBuffer();
                    break;
                case 1: 
                    switch(state) {
                        case 0:
                            if(walkPlanes(ECubeDirection::Z, false)) state++;
                            break;
                        case 1: 
                            if(walkPlanes(ECubeDirection::Z, true)) state++;
                            break;
                        case 2:  
                            if(walkPlanes(ECubeDirection::Y, false)) state++;
                            break;
                        case 3:
                            if(walkPlanes(ECubeDirection::Y, true)) state++;
                            break;
                        case 4:
                            if(walkPlanes(ECubeDirection::X, false)) state++;
                            break;
                        case 5:
                            if(walkPlanes(ECubeDirection::X, true)) state++;
                            break;
                    }
                    break;
                case 2:  
                    tmpBuffer.copyToBuffer(frame);
                    setFrameFinished();
                    break;
            }
            cycleCount++;
        }

        bool walkPlanes(ECubeDirection dir, bool reverse){
            tmpBuffer.setPlane(dir, reverse ? (15-planeIndex) : planeIndex, 1);    
            planeIndex++;
            if(planeIndex >= CUBE_EDGE_SIZE){
                planeIndex = 0;
                return true;
            }else{
                return false;
            }
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(state >= 6){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};