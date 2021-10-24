/*
 * PlaylistManager.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __PLAYLISTMANAGER_H__
#define __PLAYLISTMANAGER_H__

#include "CubeCore.h"
#include "Animation/ICyclicFrameGeneration.h"
#include "IPlaylistManager.h"

#ifndef PLATFORM_NATIVE
#include <Entropy.h>
#endif

class PlaylistManager : IPlaylistManager {
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
            // if(currentIndex < entryCount){
            //     return entries[currentIndex];
            // }else{
            //     return nullptr;
            // }
            // if(currentIndex >= 0 && currentIndex < entryCount){
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
            return (currentIndex+1) % (entryCount-1);
            //return Entropy.randomByte() % (entryCount-1);
        }

    private:  
};

#endif //__PLAYLISTMANAGER_H__