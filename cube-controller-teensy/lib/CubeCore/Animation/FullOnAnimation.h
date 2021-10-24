/*
 * FullOnAnimation.h
 *
 * Created: 23.10.2021 09:32:12
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#ifndef __FULLONANIMATION_H__
#define __FULLONANIMATION_H__

#include "CubeCore.h"
#include "FrameGenerator.h"
#include "FrameBuffer.h"

class FullOnAnimation : public FrameGenerator {
    public:
    protected:
    private:

        FrameBuffer tmpBuffer;
        uint8_t rowIndex;
        uint8_t planeIndex;

	public:
        FullOnAnimation(uint32_t const animationFrameTimeUs,
                        bool const repeatUntilTimeExeeded);
        virtual ~FullOnAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override;

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks, uint32_t const totalFrameTimeUs);

        void generateCyclicBase(uint32_t const currentTicks);

        void endFrame();

    protected:
    private:  
};

#endif //__FULLONANIMATION_H__