/*
 * NetworkStreamAnimation.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/PriorityFrameGenerator.h"
#include "Animations/IPriorityCyclicFrameGeneration.h"
#include "FrameBuffer.h"
#include "INetworkStreamAnimation.h"

class NetworkStreamAnimation : public PriorityFrameGenerator, public INetworkStreamAnimation {
    public:
    protected:
    private:
        const uint32_t networkTimeoutMs;
        uint32_t lastNetworkUpdateMs;
        bool requestPriorityStart;
        FrameBuffer networkBuffer;
        uint32_t nextTargetFrameTimeUs;
	public:
        NetworkStreamAnimation(const uint32_t networkTimeoutMs) :
                PriorityFrameGenerator(),
                networkTimeoutMs(networkTimeoutMs), 
                lastNetworkUpdateMs(0),
                requestPriorityStart(false),
                nextTargetFrameTimeUs(0) {
            networkBuffer.clearBuffer();
        }
        virtual ~NetworkStreamAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override{
            FrameGenerator::initializeFrameSequence(currentTicks);
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks){
            FrameGenerator::startFrame(nextFrame, currentTicks);
        }

        bool generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            targetFrameTimeUs = nextTargetFrameTimeUs;
            networkBuffer.copyToBuffer(frame);
            return true;
        }

        void endFrame(uint32_t const currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if((millis() - lastNetworkUpdateMs) > networkTimeoutMs){
                endAnimationInternally();
            }
        }

        virtual void startAnimation(uint32_t targetFrameTimeUs) override {
            this->requestPriorityStart = true;
            this->nextTargetFrameTimeUs = targetFrameTimeUs;
            this->lastNetworkUpdateMs = millis();
            networkBuffer.clearBuffer();
        }

        virtual void endAnimation() override{
            endAnimationInternally();
        }

        virtual void updateFrame(buffer_t *nextFrame, uint32_t targetFrameTimeUs) override{
            networkBuffer.copyFromBuffer(nextFrame);
            this->nextTargetFrameTimeUs = targetFrameTimeUs;
            this->lastNetworkUpdateMs = millis();
        }

        virtual uint32_t lastFrameTimeUs() override{
            return this->lastFrameTimeUs();    
        }

        virtual bool hasPriorityStartRequest() override{
            return requestPriorityStart;
        }

    protected:

        void endAnimationInternally(){
            this->setSequenceFinished();
            requestPriorityStart = false;
        }
    private:  
};
