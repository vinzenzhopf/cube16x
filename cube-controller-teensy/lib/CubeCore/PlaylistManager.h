/*
 * PlaylistManager.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __PLAYLISTMANAGER_H__
#define __PLAYLISTMANAGER_H__

#include "Animation/FrameGenerator.h"
#include <Entropy.h>

struct PlaylistEntry {
    FrameGenerator* generator;
    uint32_t animationDurationUs;
    bool repeatAnimation;
};

class PlaylistManager {
    public:
    protected:        
        PlaylistEntry entries[MAX_PLAYLIST_ENTRIES];
        uint8_t entryCount = 0;

        uint8_t currentIndex = 0;
    private:

	public:
        PlaylistManager(){
        }
        ~PlaylistManager(){
        }

        void addAnimation(FrameGenerator* const frameGenerator, int32_t const animationDurationUs, bool const repeatAnimation){
            entries[entryCount].generator = frameGenerator;
            entries[entryCount].animationDurationUs = animationDurationUs;
            entries[entryCount].repeatAnimation = repeatAnimation;
            entryCount++;
            random(20);
        }
        
        PlaylistEntry* getNextAnimation(){
            if(entryCount > 0){
                currentIndex = generateNewIndex();
                return getCurrentAnimation();
            }else{
                return nullptr;
            }
        }

        PlaylistEntry* getCurrentAnimation(){
            if(entryCount > 0){
                return &entries[currentIndex];
            }else{
                return nullptr;
            }
        }
        
    protected:
        uint8_t generateNewIndex(){
            return (currentIndex+1) % (entryCount-1);
            //return Entropy.randomByte() % (entryCount-1);
        }

    private:  
};

#endif //__PLAYLISTMANAGER_H__