/*
 * PlaylistManager.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __PLAYLISTMANAGER_H__
#define __PLAYLISTMANAGER_H__

#include "Animation/FrameGenerator.h"

#ifndef PLATFORM_NATIVE
#include <Entropy.h>
#endif

// struct PlaylistEntry {
//     FrameGenerator* generator;
//     uint32_t animationDurationUs;
//     bool repeatAnimation;
// };

class PlaylistManager {
    public:
    protected:        
        FrameGenerator* entries[MAX_PLAYLIST_ENTRIES];
        uint8_t entryCount = 0;

        uint8_t currentIndex = 0;
    private:

	public:
        PlaylistManager(){
        }
        ~PlaylistManager() = default;

        void addAnimation(FrameGenerator* const frameGenerator){
            entries[entryCount] = frameGenerator;
            entryCount++;
        }
        
        FrameGenerator* getNextAnimation(){
            if(entryCount > 0){
                currentIndex = generateNewIndex();
                return getCurrentAnimation();
            }else{
                return nullptr;
            }
        }

        FrameGenerator* getCurrentAnimation(){
            if(entryCount > 0){
                return entries[currentIndex];
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