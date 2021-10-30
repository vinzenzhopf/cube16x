/* 
* PlaneOutputWriter.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/

#pragma once

#include "LedCube16x.h"
#include "Base/CyclicModule.h"

enum class EPlaneDataOutputWriterState{ 
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

class PlaneDataOutputWriter final : public CyclicModule
{
//variables
public:
protected:
    const uint8_t CONTROL_CLOCK_PIN;
    const uint8_t CONTROL_STO_PIN;
    const uint8_t DATA_PIN;
    const uint8_t HIGH_CYCLE_COUNT;

    plane_t *pPlane;
    plane_t *pNextPlane;
    bool bLatchData;

    uint8_t nCycleDelay;
    uint8_t nRowIndex;
    EPlaneDataOutputWriterState eState;
private:

//functions
public:
	PlaneDataOutputWriter(
            uint8_t CONTROL_CLOCK_PIN, 
            uint8_t CONTROL_STO_PIN,
            uint8_t DATA_PIN, 
            uint8_t HIGH_CYCLE_COUNT);
	~PlaneDataOutputWriter() = default;

    void setPlane(plane_t *plane);
    void latchData();

    bool isReadyForNextPlane();
    bool isReadyToLatch();

    bool initialize() override;
    void cyclic() override;
    void reset();

protected:
    uint8_t getOutputData8();
    uint8_t getOutputData32();

private:
};

