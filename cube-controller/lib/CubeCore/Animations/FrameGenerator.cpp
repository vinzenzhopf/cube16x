

#include "FrameGenerator.h"

FrameGenerator::FrameGenerator() : FrameGenerator(0){
}

FrameGenerator::FrameGenerator(uint32_t const targetFrameTimeUs) :
        targetFrameTimeUs(targetFrameTimeUs),
        frameCounter(0),
        sequenceStartTicks(0),
        frameStartTicks(0),
        sequenceFinished(false) {
}

void FrameGenerator::initializeFrameSequence(uint32_t currentTicks){
    this->sequenceStartTicks = currentTicks;
    this->frameStartTicks = currentTicks; 
    this->lastFrameStartTicks = currentTicks;
    this->sequenceFinished = false;
    this->frameCounter = 0;
}

void FrameGenerator::startFrame(buffer_t *nextFrame, uint32_t const currentTicks){
    this->frame = nextFrame;

    this->lastFrameStartTicks = this->frameStartTicks;
    this->frameStartTicks = currentTicks; 
}

void FrameGenerator::endFrame(uint32_t const currentTicks){
    this->frameCounter++;
}

bool FrameGenerator::generateCyclicBase(uint32_t const currentTicks){
    return true;
}
