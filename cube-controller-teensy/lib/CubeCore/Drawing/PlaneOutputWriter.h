/* 
* PlaneOutputWriter.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/

#pragma once

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
            uint8_t HIGH_CYCLE_COUNT);
	virtual ~PlaneOutputWriter() = default;

    void setPlaneNumber(uint8_t nPlaneIndex);
    void latchData();

    bool isReadyForNextPlane();
    bool isReadyToLatch();

    bool initialize() override;
    void cyclic() override;
    void reset();
};

