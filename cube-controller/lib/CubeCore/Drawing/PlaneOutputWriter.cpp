/* 
* PlaneOutputWriter.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "PlaneOutputWriter.h"

PlaneOutputWriter::PlaneOutputWriter(uint8_t *PORT_CONTROL_OUT, uint8_t CONTROL_CLOCK_PIN, 
        uint8_t CONTROL_OE_PIN, uint8_t CONTROL_STO_PIN, uint8_t CONTROL_DATA_PIN, 
        uint8_t HIGH_CYCLE_COUNT) : 
            PORT_CONTROL_OUT(PORT_CONTROL_OUT),
            CONTROL_CLOCK_PIN(CONTROL_CLOCK_PIN), 
            CONTROL_OE_PIN(CONTROL_OE_PIN),
            CONTROL_STO_PIN(CONTROL_STO_PIN),
            CONTROL_DATA_PIN(CONTROL_DATA_PIN),            
            HIGH_CYCLE_COUNT(HIGH_CYCLE_COUNT) {
    eState = EPlaneOutputWriterState::eIdle;
    nCycleDelay = 0;
    nPlaneIndex = -1;
    nNextPlaneIndex -1;
    bLatchData = false;
}

PlaneOutputWriter::~PlaneOutputWriter()
{
}

bool PlaneOutputWriter::isReadyForNextPlane(){
    return eState == EPlaneOutputWriterState::eIdle;
}

bool PlaneOutputWriter::isReadyToLatch(){
    return eState == EPlaneOutputWriterState::eDataWritten;
}

void PlaneOutputWriter::setPlaneNumber(uint8_t nPlaneIndex){
    nNextPlaneIndex = nPlaneIndex;
}

void PlaneOutputWriter::latchData(){
    bLatchData = true;
}

void PlaneOutputWriter::reset(){
    eState = EPlaneOutputWriterState::eIdle;
    nCycleDelay = 0;
    nPlaneIndex = -1;
    nNextPlaneIndex -1;
    bLatchData = false;
}

void PlaneOutputWriter::cyclic(){
    CyclicModule::cyclic();

    switch (eState)
    {
    case EPlaneOutputWriterState::eIdle:
        if(nNextPlaneIndex != -1){
            eState = EPlaneOutputWriterState::eSetDataHigh;
            nShiftBitCount = 0;
            nPlaneIndex = nNextPlaneIndex;
            nNextPlaneIndex = -1;
        }
        break;

    case EPlaneOutputWriterState::eSetDataHigh:
        if(nShiftBitCount == nPlaneIndex){
            *PORT_CONTROL_OUT |= (1<<CONTROL_DATA_PIN); //HIGH
        } else {
            *PORT_CONTROL_OUT &= ~(1<<CONTROL_DATA_PIN); //Low
        }
        *PORT_CONTROL_OUT |= (1<<CONTROL_CLOCK_PIN); //HIGH
        eState = EPlaneOutputWriterState::eWaitDataHigh;
        break;

    case EPlaneOutputWriterState::eWaitDataHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eSetDataLow;
        break;

    case EPlaneOutputWriterState::eSetDataLow:
        *PORT_CONTROL_OUT &= ~(1<<CONTROL_DATA_PIN | 1<<CONTROL_CLOCK_PIN); //Low
        eState = EPlaneOutputWriterState::eWaitDataLow;

    case EPlaneOutputWriterState::eWaitDataLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT)){
            nShiftBitCount++;
            if(nShiftBitCount >= CUBE_EDGE_SIZE){
                eState = EPlaneOutputWriterState::eDataWritten;
            }else{ //Loop over each plane
                eState = EPlaneOutputWriterState::eSetDataHigh;
            }
        }
        break;
    
    case EPlaneOutputWriterState::eDataWritten:
        if(bLatchData){
            bLatchData = false;
            eState = EPlaneOutputWriterState::eSetStoHigh;
        }
        break;
        
    case EPlaneOutputWriterState::eSetStoHigh:
        *PORT_CONTROL_OUT |= (1<<CONTROL_STO_PIN); //HIGH
        eState = EPlaneOutputWriterState::eWaitStoHigh;
        break;

    case EPlaneOutputWriterState::eWaitStoHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eSetStoLow;
        break;

    case EPlaneOutputWriterState::eSetStoLow:
        *PORT_CONTROL_OUT &= ~(1<<CONTROL_STO_PIN); //Low
        eState = EPlaneOutputWriterState::eWaitStoLow;
        break;

    case EPlaneOutputWriterState::eWaitStoLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eIdle;
        break;

    default:
        eState = EPlaneOutputWriterState::eIdle;
        break;
    }
}
