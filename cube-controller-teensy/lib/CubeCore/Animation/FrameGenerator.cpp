

#include "FrameGenerator.h"

FrameGenerator::FrameGenerator(
                        uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded) : 
                            animationFrameTimeUs(animationFrameTimeUs),
                            repeatUntilTimeExeeded(repeatUntilTimeExeeded),
                            frameFinished(false),
                            sequenceFinished(false),
                            sequenceStartTicks(0),
                            lastFrameStartTicks(0),
                            totalFrameTimeUs(0),
                            frameCounter(0){
}

void FrameGenerator::restartFrameSequence(uint32_t currentTicks){
    this->sequenceStartTicks = currentTicks;
    this->sequenceFinished = false;
    this->frameCounter = 0;
}

void FrameGenerator::startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs){
    this->frame = nextFrame;
    this->frameFinished = false;
    this->lastFrameStartTicks = currentTicks;
    this->totalFrameTimeUs = totalFrameTimeUs;
}

void FrameGenerator::endFrame(){
    this->frameCounter++;
}

void FrameGenerator::generateCyclicBase(uint32_t const currentTicks){
}

bool FrameGenerator::isSequenceFinished(){
    return sequenceFinished;
}

bool FrameGenerator::isFrameFinished(){
    return frameFinished;
}
bool FrameGenerator::getFrameCounter(){
    return frameCounter;
}