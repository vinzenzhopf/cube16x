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

        bool active;
        uint32_t nextFrameNumber;
        uint32_t activeFrameNumber;
	public:
        NetworkStreamAnimation(const uint32_t networkTimeoutMs) :
                PriorityFrameGenerator(),
                networkTimeoutMs(networkTimeoutMs), 
                lastNetworkUpdateMs(0),
                requestPriorityStart(false),
                nextTargetFrameTimeUs(0),
                active(false) {
            networkBuffer.clearBuffer();
        }
        virtual ~NetworkStreamAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override{
            FrameGenerator::initializeFrameSequence(currentTicks);
            active = true;
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks){
            FrameGenerator::startFrame(nextFrame, currentTicks);
        }

        bool generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            targetFrameTimeUs = nextTargetFrameTimeUs;
            activeFrameNumber = nextFrameNumber;
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

        virtual void updateFrame(buffer_t *nextFrame, uint32_t targetFrameTimeUs, uint32_t frameNumber) override{
            networkBuffer.copyFromBuffer(nextFrame);
            this->nextTargetFrameTimeUs = targetFrameTimeUs;
            this->nextFrameNumber = frameNumber;
            this->lastNetworkUpdateMs = millis();
        }

        virtual uint32_t lastFrameTimeUs() override{
            return this->lastFrameTimeUs();    
        }

        virtual bool hasPriorityStartRequest() override{
            return requestPriorityStart;
        }

        virtual NetworkStreamAnimationStatus getAnimationStatus() override{
            NetworkStreamAnimationStatus status = NetworkStreamAnimationStatus::NotActive;
            if(active){
                status = NetworkStreamAnimationStatus::Running;
            }
            if(nextFrameNumber == activeFrameNumber){
                status |= NetworkStreamAnimationStatus::FrameRedrawn;
            }else if(nextFrameNumber > (activeFrameNumber+1)){
                status |= NetworkStreamAnimationStatus::FrameDropped;
            }
            return status;
        }

    protected:

        void endAnimationInternally(){
            this->setSequenceFinished();
            requestPriorityStart = false;
            active = false;
        }
    private:  
};
