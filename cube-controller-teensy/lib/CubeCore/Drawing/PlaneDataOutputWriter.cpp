/* 
* PlaneDataOutputWriter.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "TeensyUtils.h"
#include "PlaneDataOutputWriter.h"

PlaneDataOutputWriter::PlaneDataOutputWriter(
            uint8_t CONTROL_CLOCK_PIN, 
            uint8_t CONTROL_STO_PIN,
            uint8_t DATA_PIN, 
            uint8_t HIGH_CYCLE_COUNT) : 
                CONTROL_CLOCK_PIN(CONTROL_CLOCK_PIN), 
                CONTROL_STO_PIN(CONTROL_STO_PIN),
                DATA_PIN(DATA_PIN),
                HIGH_CYCLE_COUNT(HIGH_CYCLE_COUNT),
                eState(EPlaneDataOutputWriterState::eIdle),
                nCycleDelay(0),
                nRowIndex(-1),
                pNextPlane(nullptr),
                bLatchData(false) {
}

bool PlaneDataOutputWriter::isReadyForNextPlane(){
    return eState == EPlaneDataOutputWriterState::eIdle;
}

bool PlaneDataOutputWriter::isReadyToLatch(){
    return eState == EPlaneDataOutputWriterState::eDataWritten;
}

void PlaneDataOutputWriter::setPlane(plane_t *pPlane){
    pNextPlane = pPlane;
}

void PlaneDataOutputWriter::latchData(){
    bLatchData = true;
}

void PlaneDataOutputWriter::reset(){
    eState = EPlaneDataOutputWriterState::eIdle;
    nCycleDelay = 0;
    nRowIndex = -1;
    pNextPlane = nullptr;
    bLatchData = false;
}

uint8_t PlaneDataOutputWriter::getRowData(){
    //Build the Data-Byte together from all 32 bits of data in the plane.
    //Invert rowIndex because the 32nd bit needs to be written at first to the shift registers
    const uint8_t nRowInverted = (31-nRowIndex)%32; //% just for sanity
    
    const uint8_t byteOffset = (nRowInverted/8);
    const uint8_t bitMask = (1<<(nRowInverted%8));
    uint8_t tmp = 0;
    for(uint8_t i = 0; i < 8; i++){
        if((pPlane->asBytes[(i*SHIFT_REGISTER_DEPTH_BYTES)+byteOffset] & bitMask) > 0){
            tmp |= (1<<i);
        }
    }
    return tmp;
}

bool PlaneDataOutputWriter::initialize(){
	return true;
}

void PlaneDataOutputWriter::cyclic(){
    CyclicModule::cyclic();

    switch (eState)
    {
    case EPlaneDataOutputWriterState::eIdle:
        if(pNextPlane != nullptr){
            eState = EPlaneDataOutputWriterState::eSetDataHigh;
            nRowIndex = 0;
            pPlane = pNextPlane;
            pNextPlane = nullptr;
        }
        break;

    case EPlaneDataOutputWriterState::eSetDataHigh:
        digitalWriteByte(DATA_PIN, getRowData()); //Data for the output byte
        digitalWriteFast(CONTROL_CLOCK_PIN, HIGH);
        eState = EPlaneDataOutputWriterState::eWaitDataHigh;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneDataOutputWriterState::eWaitDataHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eSetDataLow;
        break;

    case EPlaneDataOutputWriterState::eSetDataLow:
        digitalWriteFast(CONTROL_CLOCK_PIN, LOW);
        eState = EPlaneDataOutputWriterState::eWaitDataLow;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneDataOutputWriterState::eWaitDataLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT)){
            nRowIndex++;
            if(nRowIndex >= SHIFT_REGISTER_DEPTH){
                eState = EPlaneDataOutputWriterState::eDataWritten;
            }else{ //Loop over each plane
                eState = EPlaneDataOutputWriterState::eSetDataHigh;
            }
        }
        break;
    
    case EPlaneDataOutputWriterState::eDataWritten:
        if(bLatchData){
            bLatchData = false;
            eState = EPlaneDataOutputWriterState::eSetStoHigh;
        }
        break;
        
    case EPlaneDataOutputWriterState::eSetStoHigh:
        digitalWriteFast(CONTROL_STO_PIN, HIGH);
        eState = EPlaneDataOutputWriterState::eWaitStoHigh;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneDataOutputWriterState::eWaitStoHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eSetStoLow;
        break;

    case EPlaneDataOutputWriterState::eSetStoLow:
        digitalWriteFast(CONTROL_STO_PIN, LOW);
        eState = EPlaneDataOutputWriterState::eWaitStoLow;
        //break; //No break, reduces cycle count if HIGH_CYCLE_COUNT=0/1
    case EPlaneDataOutputWriterState::eWaitStoLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eIdle;
        break;

    default:
        eState = EPlaneDataOutputWriterState::eIdle;
        break;
    }
}

