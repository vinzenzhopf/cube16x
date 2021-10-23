/*
 * AnimationController.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __ANIMATIONCONTROLLER_H__
#define __ANIMATIONCONTROLLER_H__

#include "LedCube16x.h"
#include "Base/CyclicModule.h"
#include "FrameBufferController.h"
#include "PlaylistManager.h"
#include "Animation/FrameGenerator.h"
#include <Entropy.h>

enum class FrameSequenceState {
    eStart,
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
        PlaylistManager * const playlistManager;
        uint32_t const animationFrameTimeUs;

        buffer_t *pBackBuffer;

        PlaylistEntry* currentEntry;
        FrameSequenceState frameGenerationState;

        uint32_t animationStartTicks;
    private:

	public:
        AnimationController(
            FrameBufferController *bufferController,
            PlaylistManager *playlistManager,
            uint32_t const animationFrameTimeUs) :
                bufferController(bufferController),
                playlistManager(playlistManager),
                animationFrameTimeUs(animationFrameTimeUs){
            frameGenerationState = FrameSequenceState::eStart;
            currentEntry = nullptr;
        }
        ~AnimationController(){
        }

        bool initialize(){
            return true;
        }
        
        void cyclic(){
            uint32_t currentTicks = micros();
            uint32_t elapsedFrameTimeUs = currentTicks - animationStartTicks;

            switch (frameGenerationState){
                case FrameSequenceState::eStart:
                    currentEntry = playlistManager->getNextAnimation();
                    if(currentEntry != nullptr){
                        animationStartTicks = currentTicks;
                        elapsedFrameTimeUs = currentTicks - animationStartTicks;
                        frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    }
                    break;

                case FrameSequenceState::eSequenceInitialize:
                    currentEntry->generator->restartFrameSequence(currentTicks);
                    frameGenerationState = FrameSequenceState::eWaitForFrameRequired;

                case FrameSequenceState::eWaitForFrameRequired:
                    //BackBuffer is becomes false when bufferes are switched
                    if(!bufferController->isBackBufferReady()){
                        pBackBuffer = bufferController->getBackBuffer();
                        frameGenerationState = FrameSequenceState::eNewFrame;
                    }
                    break;

                case FrameSequenceState::eNewFrame:
                    currentEntry->generator->startNewFrame(pBackBuffer, currentTicks, animationFrameTimeUs);
                    frameGenerationState = FrameSequenceState::eGenerateFrame;
                    break;

                case FrameSequenceState::eGenerateFrame:
                    currentEntry->generator->generateCyclic(currentTicks);
                    if(currentEntry->generator->isFrameFinished()){
                        frameGenerationState = FrameSequenceState::eFrameFinished;
                    }
                    break;

                case FrameSequenceState::eFrameFinished:
                    bufferController->setBackBufferReady();
                    if(currentEntry->generator->isSequenceFinished()){
                        frameGenerationState = FrameSequenceState::eSequenceFinished;
                    }else{
                        frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
                    }
                    break;

                case FrameSequenceState::eSequenceFinished:
                    if(currentEntry->repeatAnimation && 
                            elapsedFrameTimeUs < currentEntry->animationDurationUs){
                        //Repeat Animation
                        frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    }else{
                        //Start with new Animation
                        frameGenerationState = FrameSequenceState::eStart;
                    }
                    break;

                default:
                    frameGenerationState = FrameSequenceState::eStart;
                    break;
            }
        }
        
    protected:
    private:  
};

#endif //__ANIMATIONCONTROLLER_H__