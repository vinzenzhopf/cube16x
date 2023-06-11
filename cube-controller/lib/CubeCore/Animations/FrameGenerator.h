/*
 * FrameGenerator.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "ICyclicFrameGeneration.h"

class FrameGenerator : public ICyclicFrameGeneration {
    public:
        uint32_t const frameTimeUs;
        
    protected:
        buffer_t *frame;

        //uint32_t animationDurationMs;
        uint32_t frameCounter;

        uint32_t sequenceStartTicks;
        uint32_t frameStartTicks;
        
    private:
        bool frameFinished;
        bool sequenceFinished;

	public:
        FrameGenerator();
        FrameGenerator(uint32_t const frameTimeUs);
        virtual ~FrameGenerator() = default;

        /**
         * @brief Initializes an Animation sequence. 
         *        Is called after a new Animation is selected by the PlaylistManager.
         * 
         * @param currentTicks The current tick-count in ms.
         */
        virtual void initializeFrameSequence(uint32_t currentTicks) override;

        /**
         * @brief Starts the new Frame-Generation update cycle. 
         *        Is Called after the Backbuffer is Ready for a new generated Frame.
         * 
         * @param nextFrame Pointer to the backbuffer
         * @param currentTicks The current tick-count in ms.
         */
        virtual void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override;

        /**
         * @brief Called Cyclic in order to generate the frames contents.
         * 
         * @param currentTicks The current tick-count in ms.
         * @return true When the frame is fully generated. This ends the generation and 
         *              continues with endFrame().
         * @return false When the frame is not fully generated. Keeps being called, as 
         *               long as false is returned.
         */
        virtual bool generateCyclicBase(uint32_t const currentTicks) override;

        /**
         * @brief Cleanup code for ending a frame generation cycle. 
         *        Here the current Animation length should be evaluated 
         *        and @ref setSequenceFinished() "setSequenceFinished()" should be 
         *        called, to end the Animation.
         * 
         * @param currentTicks The current tick-count in ms.
         */
        virtual void endFrame(uint32_t const currentTicks) override;

        bool isSequenceFinished() override;
        bool isFrameFinished() override;
        uint32_t getFrameCounter() override;

        uint32_t getFrameTimeUs() override{
            return frameTimeUs;
        }
        bool isFreeRunning() override{
            return frameTimeUs == 0;
        }

        uint32_t inline getElapsedSequenceTime(uint32_t const currentTicks){
            return currentTicks - sequenceStartTicks;
        }
        uint32_t inline getElapsedFrameTime(uint32_t const currentTicks){
            return currentTicks - frameStartTicks;
        }
        uint32_t inline getRemainingFrameTime(uint32_t const currentTicks){
            return frameTimeUs - getElapsedFrameTime(currentTicks);
        }

        void setFrameStartTicks(uint32_t const startTicks) override{
            frameStartTicks = startTicks;
        }

        void inline setFrameFinished() override {
            frameFinished = true;
        }
    protected:
        void inline setSequenceFinished(){
            sequenceFinished = true;
        }
    private:  
};

