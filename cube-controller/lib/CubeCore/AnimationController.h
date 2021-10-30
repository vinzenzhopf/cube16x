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
#include "Animation/FrameGenerator.h"

enum class FrameSequenceState {
    eStart = 0,
    eGetNextAnimation,
    eSequenceInitialize,
    eWaitForFrameRequired,
    eNewFrame,
    eGenerateFrame,
    eFrameFinished,
    eSequenceFinished
};

class AnimationController final : public CyclicModule {
    public:
    protected:
        FrameBufferController * const bufferController;
        IPlaylistManager * const playlistManager;
        uint32_t const animationFrameTimeUs;

        buffer_t *backBuffer;

        ICyclicFrameGeneration* currentGenerator;
        FrameSequenceState frameGenerationState;

        uint32_t animationStartTicks;
    private:

	public:
        AnimationController(
            FrameBufferController *bufferController,
            IPlaylistManager *playlistManager,
            uint32_t const animationFrameTimeUs) :
                bufferController(bufferController),
                playlistManager(playlistManager),
                animationFrameTimeUs(animationFrameTimeUs),
                currentGenerator(nullptr),
                frameGenerationState(FrameSequenceState::eStart),
                animationStartTicks(0) {
        }
        ~AnimationController() = default;

        bool initialize() override{
            return true;
        }
        
        void cyclic()  override{
            uint32_t currentTicks = micros();
            // uint32_t elapsedFrameTimeUs = currentTicks - animationStartTicks;
            switch (frameGenerationState){
                case FrameSequenceState::eStart:
                    currentGenerator = playlistManager->getNextAnimation();
                    if(currentGenerator){
                        animationStartTicks = currentTicks;
                        // elapsedFrameTimeUs = currentTicks - animationStartTicks;
                        frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    }
                    break;

                case FrameSequenceState::eSequenceInitialize:
                    digitalToggleFast(40);
                    currentGenerator->initializeFrameSequence(currentTicks);
                    frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
                    break;

                case FrameSequenceState::eWaitForFrameRequired:
                    //BackBuffer becomes false when bufferes are switched
                    if(!bufferController->isBackBufferReady()){
                        backBuffer = bufferController->getBackBuffer();
                        frameGenerationState = FrameSequenceState::eNewFrame;
                    }
                    break;

                case FrameSequenceState::eNewFrame:
                    currentGenerator->startFrame(backBuffer, currentTicks, animationFrameTimeUs);
                    frameGenerationState = FrameSequenceState::eGenerateFrame;
                    break;

                case FrameSequenceState::eGenerateFrame:
                    currentGenerator->generateCyclicBase(currentTicks);
                    if(currentGenerator->isFrameFinished()){
                        frameGenerationState = FrameSequenceState::eFrameFinished;
                    }
                    break;

                case FrameSequenceState::eFrameFinished:
                    currentGenerator->endFrame();
                    bufferController->setBackBufferReady();
                    if(currentGenerator->isSequenceFinished()){
                        frameGenerationState = FrameSequenceState::eSequenceFinished;
                    }else{
                        frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
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

