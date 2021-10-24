/*
 * IPlaylistManager.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __IPLAYLISTMANAGER_H__
#define __IPLAYLISTMANAGER_H__

#include "CubeCore.h"
#include "Animation/ICyclicFrameGeneration.h"

class IPlaylistManager {
    public:
        virtual void addAnimation(ICyclicFrameGeneration *frameGenerator) = 0;
        virtual ICyclicFrameGeneration* getNextAnimation() = 0;
        virtual ICyclicFrameGeneration* getCurrentAnimation() = 0;

        virtual uint8_t getEntryCount() = 0;
        virtual uint8_t getCurrentIndex() = 0;
};

#endif //__IPLAYLISTMANAGER_H__