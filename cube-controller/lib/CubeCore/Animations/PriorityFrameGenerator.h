/*
 * PriorityFrameGenerator.h
 *
 * Created: 11.06.2023 20:43
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "FrameGenerator.h"
#include "IPriorityCyclicFrameGeneration.h"

class PriorityFrameGenerator : public FrameGenerator, public IPriorityCyclicFrameGeneration {
    public:
        PriorityFrameGenerator() : FrameGenerator(){
        };
        PriorityFrameGenerator(uint32_t const targetFrameTimeUs) : FrameGenerator(targetFrameTimeUs){
        };
        virtual ~PriorityFrameGenerator() = default;

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

        bool isSequenceFinished() override{
            return FrameGenerator::isSequenceFinished();
        }

        uint32_t getFrameCounter() override{
            return FrameGenerator::getFrameCounter();
        }

        uint32_t getTargetFrameTimeUs() override{
            return FrameGenerator::getTargetFrameTimeUs();
        }
    
        uint32_t getElapsedSequenceTime(uint32_t const currentTicks){
            return FrameGenerator::getElapsedSequenceTime(currentTicks);
        }

        uint32_t getElapsedFrameTime(uint32_t const currentTicks){
            return FrameGenerator::getElapsedFrameTime(currentTicks);
        }

        uint32_t getRemainingFrameTime(uint32_t const currentTicks){
            return FrameGenerator::getRemainingFrameTime(currentTicks);
        }

        uint32_t getLastFrameTime(){
            return FrameGenerator::getLastFrameTime();
        }

    protected:
    private:  
};

