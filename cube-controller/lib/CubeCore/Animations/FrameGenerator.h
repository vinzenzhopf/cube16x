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
    protected:
        /**
         * @brief Target time of each frame. Used by the 
         *        @ref AnimationController "AnimationController" to delay buffer-switch.
         * 
         */
        uint32_t targetFrameTimeUs;

        /**
         * @brief The pointer to the current backbuffer to write to. 
         *        Is updated when @ref startFrame() "startFrame()" is called.
         * 
         */
        buffer_t *frame;

        /**
         * @brief Current count of all generated Frames of this animation.
         *        Is automatically initialized by @ref initializeFrameSequence() "initializeFrameSequence()" 
         *        and incremented by @ref endFrame() "endFrame()".
         * 
         */
        uint32_t frameCounter;

        /**
         * @brief Stores the start-time of the animation in Microseconds.
         *        May rollover after an sequence time of 71,5 Minutes.
         * 
         */
        uint32_t sequenceStartTicks;

        /**
         * @brief Stores the beginning of the current frame as tick in Microseconds.
         *        Uses the info, that the backbuffer becomes ready as referencepoint.
         * 
         */
        uint32_t frameStartTicks;

        /**
         * @brief Stores the beginning of the last frame as tick in Microseconds.
         *        Can be used combination with @ref frameStartTicks "frameStartTicks" 
         *        to get the last frametime
         * 
         */
        uint32_t lastFrameStartTicks;
        
    private:
        bool sequenceFinished;

	public:
        FrameGenerator();
        FrameGenerator(uint32_t const targetFrameTimeUs);
        virtual ~FrameGenerator() = default;

        /**
         * @brief Initializes an Animation sequence. 
         *        Is called after a new Animation is selected by the PlaylistManager.
         * 
         * @param currentTicks The current tick-count in us.
         */
        virtual void initializeFrameSequence(uint32_t currentTicks) override;

        /**
         * @brief Starts the new Frame-Generation update cycle. 
         *        Is Called after the Backbuffer is Ready for a new generated Frame.
         * 
         * @param nextFrame Pointer to the backbuffer
         * @param currentTicks The current tick-count in us.
         */
        virtual void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override;

        /**
         * @brief Called Cyclic in order to generate the frames contents.
         * 
         * @param currentTicks The current tick-count in us.
         * @return true When the frame is fully generated. This ends the generation and 
         *              continues with endFrame().
         * @return false When the frame is not fully generated. Keeps being called, as 
         *               long as false is returned.
         */
        virtual bool generateCyclicBase(uint32_t const currentTicks) override;

        /**
         * @brief Contains cleanup code for ending a frame generation cycle. 
         *        Here the current Animation length should be evaluated 
         *        and @ref setSequenceFinished() "setSequenceFinished()" should be 
         *        called, to end the Animation.
         * 
         * @param currentTicks The current tick-count in us.
         */
        virtual void endFrame(uint32_t const currentTicks) override;

        /**
         * @brief Returns the current frame-sequence state.
         * 
         * @return true When the sequence is finished.
         * @return false When the sequence is still running.
         */
        bool isSequenceFinished() override{
            return sequenceFinished;
        }

        /**
         * @brief Gets the current frame count of this animation. 
         *        Frame-Count is incremented at the end of an frame.
         * 
         * @return uint32_t Current frame count of this Animation.
         */
        uint32_t getFrameCounter() override{
            return frameCounter;
        }

        /**
         * @brief Gets the target frametime in microseconds.
         * 
         * @return uint32_t The target frametime.
         */
        uint32_t getTargetFrameTimeUs() override{
            return targetFrameTimeUs;
        }
    
        /**
         * @brief Get the elapsed animation time in microseconds.
         * 
         * @param currentTicks 
         * @return uint32_t 
         */
        uint32_t getElapsedSequenceTime(uint32_t const currentTicks){
            return currentTicks - sequenceStartTicks;
        }

        /**
         * @brief Calculates the elapsed time of the current frame.
         * 
         * @param currentTicks 
         * @return uint32_t 
         */
        uint32_t getElapsedFrameTime(uint32_t const currentTicks){
            return currentTicks - frameStartTicks;
        }

        /**
         * @brief Calculates the remaining time a frame must be showed until the 
         *        current elapsed frametime meets the target frametime.
         * 
         * @param currentTicks The current ticks in microseconds.
         * @return uint32_t The remaining frametime in microseconds.
         */
        uint32_t getRemainingFrameTime(uint32_t const currentTicks){
            return targetFrameTimeUs - getElapsedFrameTime(currentTicks);
        }

        /**
         * @brief Calculates the last frame time in Microseconds.
         * 
         * @return uint32_t Frametime in Microseconds
         */
        uint32_t getLastFrameTime(){
            return frameStartTicks - lastFrameStartTicks;
        }

    protected:
        /**
         * @brief Marks the sequence as finished. After the current frame generation the 
         *        animation is ended. The generated Frame that was generated when this method
         *        has been called is showed without frametime monitoring.
         * 
         */
        void inline setSequenceFinished(){
            sequenceFinished = true;
        }
    private:  
};

