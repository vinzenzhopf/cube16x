/*
 * PlaneWalkerAnimation.h
 *
 * Created: 24.10.2021 23:14:23
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "FrameGenerator.h"
#include "FrameBuffer.h"

class PlaneWalkerAnimation : public FrameGenerator {
    public:
    protected:
        ECubeDirection const walkingDirection;
    private:
        FrameBuffer tmpBuffer;
        uint8_t planeIndex;
	public:
        PlaneWalkerAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded,
                        ECubeDirection const walkingDirection) :
                    FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded),
                    walkingDirection(walkingDirection),
                    planeIndex(0) {
        }
        virtual ~PlaneWalkerAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            planeIndex = 0;
            tmpBuffer.clearBuffer();
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs) override{
            FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);

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
            tmpBuffer.copyToBuffer(frame);
            setFrameFinished();
        }

        void endFrame(){
            FrameGenerator::endFrame();
            planeIndex++;
            if(planeIndex >= CUBE_EDGE_SIZE){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};