/*
 * AnimationController.h
 *
 * Created: 11.07.2017 22:03:45
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __ANIMATIONCONTROLLER_H__
#define __ANIMATIONCONTROLLER_H__

#include <LedCube16x.h>
#include <Base/CyclicModule.h>
#include <FrameBufferController.h>

enum class EAnimationType{
    eFullOn,
    eFullOff,
    eLedsAlternating,
    eWalkingLed,
    eBlink,
    ePlaneWalker,
    eColumnWalker,
    eIterateLeds,
    eRainDrops
};

struct AnimationPlaylistEntry {
    EAnimationType type;
    int16_t duration;
};

class AnimationController : public CyclicModule{
    public:
    protected:
        FrameBufferController *pBufferController;
        buffer_t *pBackBuffer;

        uint8_t nByteCounter;
        uint16_t nShortCounter;


        uint8_t nPlayListEntry = 0;
        AnimationPlaylistEntry arrPlayListEntries[1] = {
            { EAnimationType::ePlaneWalker, 200 }
        };
    private:
	public:
        AnimationController();

        uint8_t getPlayListLength(){
            return sizeof(arrPlayListEntries)/sizeof(arrPlayListEntries[0]);
        };

        bool initialize() override;
        void cyclic() override;
    protected:
        void setBufferToByte(uint8_t byte);
    private:  
};

#endif //__ANIMATIONCONTROLLER_H__