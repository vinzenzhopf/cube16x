

#include "FrameGenerator.h"

FrameGenerator::FrameGenerator() : FrameGenerator(0){
}

FrameGenerator::FrameGenerator(uint32_t const frameTimeUs) :
        frameTimeUs(frameTimeUs),
        frameCounter(0),
        sequenceStartTicks(0),
        frameStartTicks(0),
        frameFinished(false),
        sequenceFinished(false) {
}

void FrameGenerator::initializeFrameSequence(uint32_t currentTicks){
    this->sequenceStartTicks = currentTicks;
    this->frameStartTicks = currentTicks; 
    this->sequenceFinished = false;
    this->frameCounter = 0;
}

void FrameGenerator::startFrame(buffer_t *nextFrame, uint32_t const currentTicks){
    this->frame = nextFrame;
    this->frameFinished = false;
    //Dont use startframe as Tick-Start to add in compensation for buffer-switching of the last frame.
    //frameStartTicks is set from the AnimationController
    //this->frameStartTicks = currentTicks; 
}

void FrameGenerator::endFrame(uint32_t const currentTicks){
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

uint32_t FrameGenerator::getFrameCounter(){
    return frameCounter;
}