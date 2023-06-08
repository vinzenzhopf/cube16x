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

class PlaneWalkerAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        uint8_t planeIndex;
	public:
        PlaneWalkerAnimation() :
                    FrameGenerator(10000),
                    cycleCount(0),
                    planeIndex(0) {
        }
        virtual ~PlaneWalkerAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            planeIndex = 0;
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
                    tmpBuffer.setPlane(ECubeDirection::Z, planeIndex, 1);
                    break;
                case 2:  
                    tmpBuffer.copyToBuffer(frame);
                    setFrameFinished();
                    break;
            }
            cycleCount++;
            
            // for(uint8_t i = 0; i < CUBE_EDGE_SIZE; i++){
            //     //Clear Previous Rows
            //     if(planeIndex > 0){
            //         tmpBuffer.getBuffer
            //     }


            // }

            // // for(rowIndex = 0; rowIndex < CUBE_EDGE_SIZE; rowIndex++){
            //     frame->asPlanes[planeIndex].asRows[rowIndex] = 0xFFFF;
            // }
            // planeIndex++;
            // if(planeIndex >= CUBE_EDGE_SIZE){
            //     setFrameFinished();
            //     setSequenceFinished();
            // }
            // WriteTestBuffer(frame);
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            planeIndex++;
            if(planeIndex >= CUBE_EDGE_SIZE){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};