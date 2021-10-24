/* 
* PlaneOutputWriter.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "PlaneOutputWriter.h"

PlaneOutputWriter::PlaneOutputWriter(
            uint8_t CONTROL_CLOCK_PIN, 
            uint8_t CONTROL_STO_PIN, 
            uint8_t DATA_PIN, 
            uint8_t HIGH_CYCLE_COUNT) : 
                CONTROL_CLOCK_PIN(CONTROL_CLOCK_PIN), 
                CONTROL_STO_PIN(CONTROL_STO_PIN),
                DATA_PIN(DATA_PIN),            
                HIGH_CYCLE_COUNT(HIGH_CYCLE_COUNT),
                eState(EPlaneOutputWriterState::eIdle),
                nCycleDelay(0),
                nPlaneIndex(-1),
                nNextPlaneIndex(-1),
                bLatchData(false) {
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
    nNextPlaneIndex = -1;
    bLatchData = false;
}

bool PlaneOutputWriter::initialize(){
    return true;
}

void PlaneOutputWriter::cyclic(){
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
        digitalWriteFast(DATA_PIN, nShiftBitCount == nPlaneIndex ? HIGH : LOW);
        digitalWriteFast(CONTROL_CLOCK_PIN, HIGH);
        eState = EPlaneOutputWriterState::eWaitDataHigh;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneOutputWriterState::eWaitDataHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eSetDataLow;
        break;

    case EPlaneOutputWriterState::eSetDataLow:
        digitalWriteFast(DATA_PIN, LOW);
        digitalWriteFast(CONTROL_CLOCK_PIN, LOW);
        eState = EPlaneOutputWriterState::eWaitDataLow;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
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
        digitalWriteFast(CONTROL_STO_PIN, HIGH);
        eState = EPlaneOutputWriterState::eWaitStoHigh;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneOutputWriterState::eWaitStoHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eSetStoLow;
        break;

    case EPlaneOutputWriterState::eSetStoLow:
        digitalWriteFast(CONTROL_STO_PIN, LOW);
        eState = EPlaneOutputWriterState::eWaitStoLow;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneOutputWriterState::eWaitStoLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneOutputWriterState::eIdle;
        break;

    default:
        eState = EPlaneOutputWriterState::eIdle;
        break;
    }
}
