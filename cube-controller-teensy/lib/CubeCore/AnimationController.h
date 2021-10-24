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
        PlaylistManager * const playlistManager;
        uint32_t const animationFrameTimeUs;

        buffer_t *backBuffer;

        FrameGenerator* currentGenerator;
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
            currentGenerator = nullptr;
        }
        ~AnimationController(){
        }

        bool initialize() override{
            return true;
        }
        
        void cyclic()  override{
            uint32_t currentTicks = micros();
            uint32_t elapsedFrameTimeUs = currentTicks - animationStartTicks;
            switch (frameGenerationState){
                case FrameSequenceState::eStart:
                    currentGenerator = playlistManager->getNextAnimation();
                    if(currentGenerator != nullptr){
                        animationStartTicks = currentTicks;
                        elapsedFrameTimeUs = currentTicks - animationStartTicks;
                        frameGenerationState = FrameSequenceState::eSequenceInitialize;
                    }
                    break;

                case FrameSequenceState::eSequenceInitialize:
                    digitalToggleFast(40);
                    currentGenerator->restartFrameSequence(currentTicks);
                    frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
                    break;

                // case FrameSequenceState::eWaitForFrameRequired:
                //     //BackBuffer becomes false when bufferes are switched
                //     if(!bufferController->isBackBufferReady()){
                //         backBuffer = bufferController->getBackBuffer();
                //         frameGenerationState = FrameSequenceState::eNewFrame;
                //     }
                //     break;

            //     case FrameSequenceState::eNewFrame:
            //         currentGenerator->startFrame(backBuffer, currentTicks, animationFrameTimeUs);
            //         frameGenerationState = FrameSequenceState::eGenerateFrame;
            //         break;

            //     case FrameSequenceState::eGenerateFrame:
            //         currentGenerator->generateCyclicBase(currentTicks);
            //         if(currentGenerator->isFrameFinished()){
            //             frameGenerationState = FrameSequenceState::eFrameFinished;
            //         }
            //         break;

            //     case FrameSequenceState::eFrameFinished:
            //         currentGenerator->endFrame();
            //         bufferController->setBackBufferReady();
            //         if(currentEntry->generator->isSequenceFinished()){
            //             frameGenerationState = FrameSequenceState::eSequenceFinished;
            //         }else{
            //             frameGenerationState = FrameSequenceState::eWaitForFrameRequired;
            //         }
            //         break;

            //     case FrameSequenceState::eSequenceFinished:
            //         if(currentEntry->repeatAnimation && 
            //                 elapsedFrameTimeUs < currentEntry->animationDurationUs){
            //             //Repeat Animation
            //             frameGenerationState = FrameSequenceState::eSequenceInitialize;
            //         }else{
            //             //Start with new Animation
            //             frameGenerationState = FrameSequenceState::eStart;
            //         }
            //         break;

            //     default:
            //         frameGenerationState = FrameSequenceState::eStart;
            //         break;
            }
        }
        
    protected:
    private:  
};

#endif //__ANIMATIONCONTROLLER_H__