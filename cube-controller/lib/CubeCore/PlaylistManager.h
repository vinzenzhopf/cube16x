/*
 * PlaylistManager.h
 *
 * Created: 23.10.2021 10:03:38
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/ICyclicFrameGeneration.h"
#include "Animations/IPriorityCyclicFrameGeneration.h"
#include "IPlaylistManager.h"

#ifndef PLATFORM_NATIVE
#include <Entropy.h>
#endif

#define NO_ACTIVE_PRIORITY_INDEX (-1)

class PlaylistManager : public IPlaylistManager {
    public:
    protected:        
        ICyclicFrameGeneration *entries[MAX_PLAYLIST_ENTRIES];
        IPriorityCyclicFrameGeneration *priorityEntries[MAX_PRIORITY_ANIMATION_ENTRIES];
        int8_t entryCount;
        int8_t priorityEntryCount;
        int8_t currentIndex;
        int8_t currentPriorityIndex;
    private:

	public:
        PlaylistManager() : 
            entryCount(0),
            priorityEntryCount(0),
            currentIndex(0), //Initialize to last index, so that it is advanced to the first animation.
            currentPriorityIndex(-1)
        {
        }
        ~PlaylistManager() = default;

        void addAnimation(ICyclicFrameGeneration *frameGenerator) override{
            if(entryCount >= MAX_PLAYLIST_ENTRIES){
                Serial.println("ERROR: Too Many Playlists entries added!");
                return;
            }
            entries[entryCount] = frameGenerator;
            currentIndex = entryCount;
            entryCount++;
        }

        void addPriorityAnimation(IPriorityCyclicFrameGeneration *frameGenerator) override{
            if(priorityEntryCount >= MAX_PRIORITY_ANIMATION_ENTRIES){
                Serial.println("ERROR: Too Many Playlists entries added!");
                return;
            }
            priorityEntries[priorityEntryCount] = frameGenerator;
            priorityEntryCount++;
        }
        
        ICyclicFrameGeneration* getNextAnimation() override{
            if(entryCount > 0){
                selectNextAnimation();
                return getCurrentAnimation();
            }else{
                return nullptr;
            }
        }

        ICyclicFrameGeneration* getCurrentAnimation() override{
            if(currentPriorityIndex != NO_ACTIVE_PRIORITY_INDEX){
                return priorityEntries[currentPriorityIndex];
            }else if(currentIndex >= 0 && currentIndex < entryCount){
                return entries[currentIndex];
            }
            return nullptr;
        }

        bool hasPriorityRequest() override{
            return (this->getPriorityRequest() != NO_ACTIVE_PRIORITY_INDEX);
        }
        
    protected:
        int8_t generateNextIndex(){
            return (currentIndex+1) % (entryCount);
            //return Entropy.randomByte() % (entryCount-1);
        }

        void selectNextAnimation(){
            int8_t nextPriorityIndex = getPriorityRequest();
            if(nextPriorityIndex != NO_ACTIVE_PRIORITY_INDEX){
                currentPriorityIndex = nextPriorityIndex;
                return;
            }
            currentPriorityIndex = NO_ACTIVE_PRIORITY_INDEX;
            currentIndex = generateNextIndex();
        }

        int8_t getPriorityRequest(){
            for(int8_t i = 0; i < priorityEntryCount; i++){
                if(priorityEntries[i] != nullptr && priorityEntries[i]->hasPriorityStartRequest()){
                    return i;
                }
            }
            return NO_ACTIVE_PRIORITY_INDEX;
        }

    private:  
};

