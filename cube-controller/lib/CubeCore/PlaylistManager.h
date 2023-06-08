/*
 * PlaylistManager.h
 *
 * Created: 23.10.2021 10:03:38
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/ICyclicFrameGeneration.h"
#include "IPlaylistManager.h"

#ifndef PLATFORM_NATIVE
#include <Entropy.h>
#endif

class PlaylistManager : public IPlaylistManager {
    public:
    protected:        
        ICyclicFrameGeneration *entries[MAX_PLAYLIST_ENTRIES];
        int8_t entryCount;
        int8_t currentIndex;
    private:

	public:
        PlaylistManager() : 
            entryCount(0),
            currentIndex(0) {
        }
        ~PlaylistManager() = default;

        void addAnimation(ICyclicFrameGeneration *frameGenerator) override{
            entries[entryCount] = frameGenerator;
            entryCount++;
        }
        
        ICyclicFrameGeneration* getNextAnimation() override{
            if(entryCount > 0){
                currentIndex = generateNewIndex();
                return getCurrentAnimation();
            }else{
                return nullptr;
            }
        }

        ICyclicFrameGeneration* getCurrentAnimation() override{
            return entries[currentIndex];
            // Why is this not working??
            // if(currentIndex >= 0){
            //     return entries[currentIndex];
            // }else{
            //     return nullptr;
            // }
        }

        uint8_t getEntryCount() override{
            return (uint8_t)entryCount;
        }

        uint8_t getCurrentIndex() override{
            return (uint8_t)currentIndex;
        }
        
    protected:
        int8_t generateNewIndex(){
            return (currentIndex+1) % (entryCount);
            //return Entropy.randomByte() % (entryCount-1);
        }

    private:  
};

