/*
 * AnimationController.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "LedCube16x.h"
#include "Base/CyclicModule.h"
#include "FrameBufferController.h"
#include "IPlaylistManager.h"
#include "Animations/FrameGenerator.h"
#include "FrameStatistics.h"

enum class FrameSequenceState {
    eStart = 0,
    eGetNextAnimation,
    eSequenceInitialize,
    eWaitForFrameRequired,
    eNewFrame,
    eGenerateFrame,
    eFrameFinished,
    eAdjustFrameTime,
    eSequenceFinished
};

class AnimationController final : public CyclicModule {
    public:
    protected:
        FrameBufferController * const bufferController;
        IPlaylistManager * const playlistManager;
        FrameStatistics * const frameStatistics;
        uint32_t const animationFrameTimeUs;

        buffer_t *backBuffer;

        ICyclicFrameGeneration* currentGenerator;
        FrameSequenceState frameGenerationState;

    private:

	public:
        AnimationController(
            FrameBufferController *bufferController,
            IPlaylistManager *playlistManager,
            FrameStatistics *frameStatistics,
            uint32_t const animationFrameTimeUs) :
                bufferController(bufferController),
                playlistManager(playlistManager),
                frameStatistics(frameStatistics),
                animationFrameTimeUs(animationFrameTimeUs),
                currentGenerator(nullptr),
                frameGenerationState(FrameSequenceState::eStart) {
        }
        ~AnimationController() = default;

        bool initialize() override{
            return true;
        }
        
        void cyclic()  override{
            uint32_t currentTicks = micros();
            switch (frameGenerationState){
                case FrameSequenceState::eStart:
                    currentGenerator = playlistManager->getNextAnimation();
                    if(currentGenerator){
                        frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    }
                    break;

                case FrameSequenceState::eSequenceInitialize:
                    currentGenerator->initializeFrameSequence(currentTicks);
                    frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
                    break;

                case FrameSequenceState::eWaitForFrameRequired:
                    //BackBuffer becomes false when bufferes are switched
                    if(!bufferController->isBackBufferReady()){
                        backBuffer = bufferController->getBackBuffer();
                        frameGenerationState = FrameSequenceState::eNewFrame;
                    }else{
                        break;
                    }
                case FrameSequenceState::eNewFrame:
                    digitalWriteFast(40, HIGH);
                    currentGenerator->startFrame(backBuffer, currentTicks);
                    frameStatistics->startFrame(currentTicks);
                    frameGenerationState = FrameSequenceState::eGenerateFrame;
                    break;

                case FrameSequenceState::eGenerateFrame:
                    currentGenerator->generateCyclicBase(currentTicks);
                    if(currentGenerator->isFrameFinished()){
                        frameGenerationState = FrameSequenceState::eFrameFinished;
                    }
                    break;

                case FrameSequenceState::eFrameFinished:
                    digitalWriteFast(40, LOW);
                    currentGenerator->endFrame(currentTicks);
                    frameStatistics->endFrame(currentTicks);
                    frameGenerationState = FrameSequenceState::eAdjustFrameTime;

                case FrameSequenceState::eAdjustFrameTime:
                    if(currentGenerator->isFreeRunning() ||
                        currentGenerator->getElapsedFrameTime(currentTicks) >= currentGenerator->getFrameTimeUs()){
                        
                        bufferController->setBackBufferReady();
                        currentGenerator->setFrameStartTicks(currentTicks);

                        if(currentGenerator->isSequenceFinished()){
                            frameGenerationState = FrameSequenceState::eSequenceFinished;
                        }else{
                            frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
                        }
                    }
                    break;

                case FrameSequenceState::eSequenceFinished:
                    // if(currentGenerator->getRepeatUntilTimeExceeded && 
                    //         elapsedFrameTimeUs < currentGenerator->getAnimationFrameTimeUs){
                    //     //Repeat Animation
                    //     frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    // }else{
                        //Start with new Animation
                        frameGenerationState = FrameSequenceState::eStart;
                    // }
                    break;

                default:
                    frameGenerationState = FrameSequenceState::eStart;
                    break;
            }
        }
        
    protected:
    private:  
};

