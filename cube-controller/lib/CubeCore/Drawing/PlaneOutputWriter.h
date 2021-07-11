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

class PlaneOutputWriter : public CyclicModule
{
//variables
public:
protected:
    volatile uint8_t * const PORT_CTRL_OUT;
    const uint8_t CONTROL_CLOCK_PIN;
    const uint8_t CONTROL_STO_PIN;
    const uint8_t CONTROL_DATA_PIN;
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
        volatile uint8_t *PORT_CTRL_OUT, 
        uint8_t CONTROL_CLOCK_PIN, 
        uint8_t CONTROL_STO_PIN, 
        uint8_t CONTROL_DATA_PIN, 
        uint8_t HIGH_CYCLE_COUNT);
	~PlaneOutputWriter();

    void setPlaneNumber(uint8_t nPlaneIndex);
    void latchData();

    bool isReadyForNextPlane();
    bool isReadyToLatch();

    bool initialize() override;
    void cyclic() override;
    void reset();
};

#endif //__PLANEOUTPUTWRITER_H__