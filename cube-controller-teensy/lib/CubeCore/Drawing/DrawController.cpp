/* 
* DrawController.cpp
*
* Created: 08.07.2021 18:36:46
* Author: vhopf
*/


#include "DrawController.h"

void DrawController::reset(){
    eState = EDrawControllerState::eIdle;
    nPlaneIndex = 0;
    this->resetCycleTimeout();
}

bool DrawController::initialize(){
	return true;
}


void DrawController::cyclic(){
    CyclicModule::cyclic();

    switch (eState)
    {
    case EDrawControllerState::eIdle:
    case EDrawControllerState::eCheckBackBufferReady:  
        if(pFrameBufferController->isBackBufferReady()){
            pFrameBufferController->switchBuffers();
            pFrame = pFrameBufferController->getFrontBuffer();
        }
        nPlaneIndex = 0;
        eState = EDrawControllerState::eLoadPlane;
        break;

    case EDrawControllerState::eLoadPlane:
        if(pPlaneOutputWriter->isReadyForNextPlane() && pPlaneDataOutputWriter->isReadyForNextPlane()){
            pPlaneDataOutputWriter->setPlane(&(pFrame->asPlanes[nPlaneIndex]));
            pPlaneOutputWriter->setPlaneNumber(nPlaneIndex);
            eState = EDrawControllerState::eWaitForDataWritten;
        }
        break;
        
    case EDrawControllerState::eWaitForDataWritten:
        if(pPlaneOutputWriter->isReadyToLatch() && pPlaneDataOutputWriter->isReadyToLatch()){
            pPlaneOutputWriter->latchData();
            pPlaneDataOutputWriter->latchData();
            eState = EDrawControllerState::eAdvancePlaneCounter;
        }
        break;

    case EDrawControllerState::eAdvancePlaneCounter:
        if(waitCycleTimeout(PLANE_DELAY_COUNT)){
            nPlaneIndex++;
            if(nPlaneIndex >= CUBE_EDGE_SIZE){
                eState = EDrawControllerState::eCompleteBufferWritten;
                pFrameBufferController->setFrontBufferReady();
            }else{
                eState = EDrawControllerState::eLoadPlane;
            }
        }
        break;

    case EDrawControllerState::eCompleteBufferWritten:
        pOutputEnableGuard->setDataReady(true);
        eState = EDrawControllerState::eCheckBackBufferReady;
        break;

    default:
        eState = EDrawControllerState::eIdle;
        pOutputEnableGuard->setDataReady(false);
        break;
    }
}
