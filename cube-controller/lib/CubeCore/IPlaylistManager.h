/*
 * IPlaylistManager.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/ICyclicFrameGeneration.h"

class IPlaylistManager {
    public:
        virtual void addAnimation(ICyclicFrameGeneration *frameGenerator) = 0;
        virtual void addPriorityAnimation(IPriorityCyclicFrameGeneration *frameGenerator) = 0;

        virtual ICyclicFrameGeneration* getNextAnimation() = 0;
        virtual ICyclicFrameGeneration* getCurrentAnimation() = 0;

        virtual bool hasPriorityRequest() = 0;
};

