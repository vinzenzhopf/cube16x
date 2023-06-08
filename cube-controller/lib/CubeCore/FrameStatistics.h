/*
 * FrameStatistics.h
 *
 * Created: 08.06.2023 12:51:05
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "LedCube16x.h"
#include "Base/CyclicModule.h"
#include "Util/StatisticArray.h"

class FrameStatistics final : public CyclicModule {
    public:
    protected:
        StatisticArray<uint32_t, 10, UINT32_MAX> _frameData;
        StatisticArray<uint32_t, 10, UINT32_MAX> _updateData;

        uint32_t _startTicks;
        uint32_t _endTicks;
        uint32_t _frameTime;
        uint32_t _updateTime;

        uint32_t _frameCount;
        bool _newFrame;
    private:
	public:
        FrameStatistics() :
                _frameData(),
                _updateData() {
        }
        ~FrameStatistics() = default;

        bool initialize() override{
            return true;
            _startTicks = micros();
        }
        
        void cyclic()  override{
            if(_newFrame){
                Serial.printf("Frame:%6d;Ft:%6dus;FtMean:%6.3fus;Ut:%4dus;UtMean:%3.3fus\n", 
                    _frameCount, _frameData.Last(), _frameData.Mean(), _updateData.Last(), _updateData.Mean());
            }
            _newFrame = false;
        }

        void startFrame(uint32_t startTicks){
            _frameTime = startTicks - _startTicks;
            _startTicks = startTicks;

            _frameData.push(_frameTime);
            _updateData.push(_updateTime);

            _frameCount++;
            _newFrame = true;
        }

        void endFrame(uint32_t endTicks){
            _endTicks = endTicks;
            _updateTime = endTicks - _startTicks;
        }

    protected:
        void resetBuffer(){
            _frameData.resetBuffer();
            _updateData.resetBuffer();
        }
        
    private:  
};

