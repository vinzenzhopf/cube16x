/*
 * BouncingCubeAnimation.h
 *
 * Created: 25.10.2021 19:16:18
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
#include "FrameBuffer.h"
#include "Util/PlaneUtil.h"
#include "Util/CubeMath.h"
#include "Util/IntVectors.h"

#include "Entropy.h"

class BouncingCubeAnimation : public FrameGenerator {
    public:
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        IntCube cube;

        uint8_t state;
        uint8_t iter;
        uint8_t pos;

        IntVector3D v1;
        IntVector3D v2;
	public:
        BouncingCubeAnimation() :
                    FrameGenerator(80000), 
                    cycleCount(0),
                    state(0) {
        }
        virtual ~BouncingCubeAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override {
            FrameGenerator::initializeFrameSequence(currentTicks);
            cube.set(0, 0, 0, 15);
            state = 0;
            pos = 0;
            iter = 0;
        }

        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override{
            FrameGenerator::startFrame(nextFrame, currentTicks);
            cycleCount = 0;
        }

        void generateCyclicBase(uint32_t const currentTicks){
            FrameGenerator::generateCyclicBase(currentTicks);
            switch(cycleCount){
                case 0:
                    tmpBuffer.clearBuffer();
                    break;
                case 1:
                    switch (state)
                    {
                    case 0: //Shrink to middle
                        cube.set(pos, pos, pos, 16-pos*2);
                        if(pos >= 7) state++;
                        else pos++;
                        break;
                    case 1: //Expand to max
                        cube.set(pos, pos, pos, 16-pos*2);    
                        if(pos == 0){
                            iter++;
                            if(iter >= 3)
                                state = 0;
                            else
                                state++;
                        } else pos--;
                        break;
                    case 2:
                        pos = 15;
                        iter = 0;
                        state++;
                    case 3: //Morph to edge
                        setCubeDimension(iter, pos);
                        if(pos == 0) state++;
                        else pos--;
                        break;
                    case 4: //Morph back
                        setCubeDimension(iter, pos);
                        if(pos >= 15) state++;
                        else pos++;
                        break;
                    case 5:
                        iter++;
                        if(iter > 3)
                            state++;
                        else
                            state = 3;
                    default:
                        break;
                    }
                case 2:
                    cube.drawCubeWireframe(&tmpBuffer);
                case 3:  
                    tmpBuffer.copyToBuffer(frame);
                    setFrameFinished();
                    break;
            }
            cycleCount++;
        }

        void setCubeDimension(uint8_t edgeNum, uint8_t frame){
            switch (edgeNum)
            {
            case 0:
                v1.set(0, 0, 0);
                v2.set(frame, frame, frame);
                break;
            case 1:
                v1.set(15, 0, 15);
                v2.set(15-frame, frame, 15-frame);
                break;
            case 2:
                v1.set(15, 15, 0);
                v2.set(15-frame, 15-frame, frame);
                break;
            case 3:
                v1.set(0, 15, 15);
                v2.set(frame, 15-frame, 15-frame);
                break;
            default:
                break;
            }
            cube.set(v1, v2);
        }

        void endFrame(uint32_t currentTicks){
            FrameGenerator::endFrame(currentTicks);
            if(state > 5){
                setSequenceFinished();
            }
        }

    protected:
    private:  
};