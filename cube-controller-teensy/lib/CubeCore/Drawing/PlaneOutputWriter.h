/* 
* PlaneOutputWriter.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#ifndef __PLANEOUTPUTWRITER_H__
#define __PLANEOUTPUTWRITER_H__

#include "LedCube16x.h"
#include "Base/CyclicModule.h"

enum class EPlaneOutputWriterState{ 
    eIdle,
    eSetDataHigh,
    eWaitDataHigh,
    eSetDataLow,
    eWaitDataLow,
    eDataWritten,
    eSetStoHigh,
    eWaitStoHigh,
    eSetStoLow,
    eWaitStoLow,
    eFinished
};

class PlaneOutputWriter final : public CyclicModule
{
//variables
public:
protected:
    const uint8_t CONTROL_CLOCK_PIN;
    const uint8_t CONTROL_STO_PIN;
    const uint8_t DATA_PIN;
    const uint8_t HIGH_CYCLE_COUNT;

    int8_t nPlaneIndex;
    int8_t nNextPlaneIndex;
    bool bLatchData;
    uint8_t nCycleDelay;
    uint8_t nShiftBitCount;

    EPlaneOutputWriterState eState;
private:

//functions
public:
	PlaneOutputWriter(
            uint8_t CONTROL_CLOCK_PIN, 
            uint8_t CONTROL_STO_PIN, 
            uint8_t DATA_PIN, 
            uint8_t HIGH_CYCLE_COUNT) : 
                CONTROL_CLOCK_PIN(CONTROL_CLOCK_PIN), 
                CONTROL_STO_PIN(CONTROL_STO_PIN),
                DATA_PIN(DATA_PIN),            
                HIGH_CYCLE_COUNT(HIGH_CYCLE_COUNT) {
        eState = EPlaneOutputWriterState::eIdle;
        nCycleDelay = 0;
        nPlaneIndex = -1;
        nNextPlaneIndex = -1;
        bLatchData = false;
    }
    
	~PlaneOutputWriter() {
    }

    void setPlaneNumber(uint8_t nPlaneIndex);
    void latchData();

    bool isReadyForNextPlane();
    bool isReadyToLatch();

    bool initialize();
    void cyclic();
    void reset();
};

#endif //__PLANEOUTPUTWRITER_H__