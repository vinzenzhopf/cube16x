/*
 * INetworkStreamAnimation.h
 *
 * Created: 11.06.2023 15:54
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"

enum NetworkStreamAnimationStatus : uint8_t
{
    NotActive       = 0b00000000,
    Running         = 0b00000001,
    PackageLost     = 0b00000100, // Network package lost, receive order wrong.
    FrameDropped    = 0b00001000, // Frame dropped, too many frames to show.
    FrameRedrawn    = 0b00010000, // Received too slow, frame has been redrawn.
};

inline NetworkStreamAnimationStatus operator|(NetworkStreamAnimationStatus a, NetworkStreamAnimationStatus b)
{
    return static_cast<NetworkStreamAnimationStatus>(static_cast<int>(a) | static_cast<int>(b));
}

inline NetworkStreamAnimationStatus operator|=(NetworkStreamAnimationStatus a, NetworkStreamAnimationStatus b)
{
    return static_cast<NetworkStreamAnimationStatus>(static_cast<int>(a) | static_cast<int>(b));
}

class INetworkStreamAnimation
{
    public:
        virtual void startAnimation(uint32_t targetFrameTimeUs) = 0;
        virtual void endAnimation() = 0;
        virtual void updateFrame(buffer_t *nextFrame, uint32_t targetFrameTimeUs, uint32_t frameNumber) = 0;
        virtual uint32_t lastFrameTimeUs() = 0;
        virtual NetworkStreamAnimationStatus getAnimationStatus() = 0;
};
