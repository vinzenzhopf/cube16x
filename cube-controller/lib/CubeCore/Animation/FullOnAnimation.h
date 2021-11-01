/*
 * FullOnAnimation.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "FrameGenerator.h"
#include "FrameBuffer.h"

class FullOnAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint8_t rowIndex;
        uint8_t planeIndex;
	public:
        FullOnAnimation() : 
                    FrameGenerator(10000), 
                    rowIndex(0),
                    planeIndex(0) {
            tmpBuffer.setBuffer();
        }
        virtual ~FullOnAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override{
            FrameGenerator::initializeFrameSequence(currentTicks);
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks){
            FrameGenerator::startFrame(nextFrame, currentTicks);
            rowIndex = 0;
            planeIndex = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            // for(rowIndex = 0; rowIndex < CUBE_EDGE_SIZE; rowIndex++){
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

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(frameCounter >= 400){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};
