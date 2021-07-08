/* 
* DrawController.cpp
*
* Created: 08.07.2021 18:36:46
* Author: vhopf
*/


#include "DrawController.h"


DrawController::DrawController(
        PlaneOutputWriter *pPlaneOutputWriter, 
        PlaneDataOutputWriter *pPlaneDataOutputWriter,
        FrameBufferController *pFrameBufferController,
        uint8_t PLANE_DELAY_COUNT) :
            pPlaneOutputWriter(pPlaneOutputWriter),
            pPlaneDataOutputWriter(pPlaneDataOutputWriter),
            pFrameBufferController(pFrameBufferController),
            PLANE_DELAY_COUNT(PLANE_DELAY_COUNT) {
    eState = EDrawControllerState::eIdle;
}

DrawController::~DrawController()
{
}

void DrawController::reset(){
    eState = EDrawControllerState::eIdle;
    nPlaneIndex = 0;
    this->resetCycleTimeout();
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
        eState = EDrawControllerState::eInitCubeDrawing;
        break;

    case EDrawControllerState::eInitCubeDrawing:
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
            eState = EDrawControllerState::eWaitForSto;
        }
        break;

    case EDrawControllerState::eAdvancePlaneCounter:
        if(waitCycleTimeout(PLANE_DELAY_COUNT)){
            nPlaneIndex++;
            if(nPlaneIndex >= CUBE_EDGE_SIZE){
                eState = EDrawControllerState::eCheckBackBufferReady;
                pFrameBufferController->setFrontBufferReady(true);
            }else{
                eState = EDrawControllerState::eLoadPlane;
            }
        }
        break;

    default:
        eState = EDrawControllerState::eIdle;
        break;
    }
}
