

#include "FullOnAnimation.h"

FullOnAnimation::FullOnAnimation(
                uint32_t const animationFrameTimeUs,
                bool const repeatUntilTimeExeeded) : 
            FrameGenerator(animationFrameTimeUs, repeatUntilTimeExeeded){
    tmpBuffer.setBuffer();
}

void FullOnAnimation::restartFrameSequence(uint32_t currentTicks){
    FrameGenerator::restartFrameSequence(currentTicks);
}

void FullOnAnimation::startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs){
    FrameGenerator::startFrame(nextFrame, currentTicks, totalFrameTimeUs);
    rowIndex = 0;
    planeIndex = 0;
}

void FullOnAnimation::generateCyclicBase(uint32_t const currentTicks){
    FrameGenerator::generateCyclicBase(currentTicks);
    // for(rowIndex = 0; rowIndex < CUBE_EDGE_SIZE; rowIndex++){
    //     frame->asPlanes[planeIndex].asRows[rowIndex] = 0xFFFF;
    // }
    // planeIndex++;
    // if(planeIndex >= CUBE_EDGE_SIZE){
    //     setFrameFinished();
    //     setSequenceFinished();
    // }
    //WriteTestBuffer(frame);
    // tmpBuffer.copyToBuffer(frame);
    // setFrameFinished();
    // setSequenceFinished();
}
