/* 
* PlaneDataOutputWriter.cpp
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#include "PlaneDataOutputWriter.h"


PlaneDataOutputWriter::PlaneDataOutputWriter(
        uint8_t *PORT_DATA_OUT, uint8_t *PORT_CONTROL_OUT, 
        uint8_t CONTROL_CLOCK_PIN, uint8_t CONTROL_OE_PIN, 
        uint8_t CONTROL_STO_PIN, uint8_t HIGH_CYCLE_COUNT) : 
            PORT_DATA_OUT(PORT_DATA_OUT),
            PORT_CONTROL_OUT(PORT_CONTROL_OUT),
            CONTROL_CLOCK_PIN(CONTROL_CLOCK_PIN), 
            CONTROL_OE_PIN(CONTROL_OE_PIN),
            CONTROL_STO_PIN(CONTROL_STO_PIN),
            HIGH_CYCLE_COUNT(HIGH_CYCLE_COUNT) {
    eState = EPlaneDataOutputWriterState::eIdle;
    nCycleDelay = 0;
    nRowIndex = -1;
    pNextPlane = nullptr;
    bLatchData = false;
}

PlaneDataOutputWriter::~PlaneDataOutputWriter()
{
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
    const uint8_t byteOffset = (nRowIndex/8);
    const uint8_t bitMask = (1<<(nRowIndex%8));
    uint8_t tmp = 0;
    for(uint8_t i = 0; i < 8; i++){
        if((pPlane->asBytes[(i*SHIFT_REGISTER_DEPTH_BYTES)+byteOffset] & bitMask) > 0){
            tmp |= (1<<i);
        }
    }
    return tmp;
}

void PlaneDataOutputWriter::cyclic(){
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
        *PORT_DATA_OUT = getRowData(); //Data for the output byte
        *PORT_CONTROL_OUT |= (1<<CONTROL_CLOCK_PIN); //HIGH
        eState = EPlaneDataOutputWriterState::eWaitDataHigh;
        break;

    case EPlaneDataOutputWriterState::eWaitDataHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eSetDataLow;
        break;

    case EPlaneDataOutputWriterState::eSetDataLow:
        *PORT_CONTROL_OUT &= ~(1<<CONTROL_CLOCK_PIN); //Low
        eState = EPlaneDataOutputWriterState::eWaitDataLow;

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
        *PORT_CONTROL_OUT |= (1<<CONTROL_STO_PIN); //HIGH
        eState = EPlaneDataOutputWriterState::eWaitStoHigh;
        break;

    case EPlaneDataOutputWriterState::eWaitStoHigh:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eSetStoLow;
        break;

    case EPlaneDataOutputWriterState::eSetStoLow:
        *PORT_CONTROL_OUT &= ~(1<<CONTROL_STO_PIN); //Low
        eState = EPlaneDataOutputWriterState::eWaitStoLow;
        break;

    case EPlaneDataOutputWriterState::eWaitStoLow:
        if(waitCycleTimeout(HIGH_CYCLE_COUNT))
            eState = EPlaneDataOutputWriterState::eIdle;
        break;

    default:
        eState = EPlaneDataOutputWriterState::eIdle;
        break;
    }
}

