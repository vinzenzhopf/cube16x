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

enum EPlaneOutputWriterState : uint8_t{ 
    eIdle = 0,
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

class PlaneOutputWriter : public CyclicModule
{
//variables
public:
protected:
    uint8_t * const PORT_CONTROL_OUT;
    const uint8_t CONTROL_CLOCK_PIN;
    const uint8_t CONTROL_OE_PIN;
    const uint8_t CONTROL_STO_PIN;
    const uint8_t CONTROL_DATA_PIN;
    const uint8_t HIGH_CYCLE_COUNT;

    uint8_t nPlaneIndex;
    uint8_t nNextPlaneIndex;
    bool bLatchData;
    uint8_t nCycleDelay;
    uint8_t nShiftBitCount;

    EPlaneOutputWriterState eState;
private:

//functions
public:
	PlaneOutputWriter(uint8_t *PORT_CONTROL_OUT, uint8_t CONTROL_CLOCK_PIN, 
        uint8_t CONTROL_OE_PIN, uint8_t CONTROL_STO_PIN, uint8_t CONTROL_DATA_PIN, 
        uint8_t HIGH_CYCLE_COUNT);
	~PlaneOutputWriter();

    void setPlaneNumber(uint8_t nPlaneIndex);
    void latchData();

    bool isReadyForNextPlane();
    bool isReadyToLatch();

    void cyclic();
    void reset();
};

#endif //__PLANEOUTPUTWRITER_H__