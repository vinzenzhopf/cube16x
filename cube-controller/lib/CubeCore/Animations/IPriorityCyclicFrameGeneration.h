/*
 * IPriorityCyclicFrameGeneration.h
 *
 * Created: 11.06.2023 16:41
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "ICyclicFrameGeneration.h"

class IPriorityCyclicFrameGeneration : public ICyclicFrameGeneration
{
    public:
        virtual bool hasPriorityStartRequest() = 0;
};

