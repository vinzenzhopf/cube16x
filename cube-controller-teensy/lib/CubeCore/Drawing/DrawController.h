/* 
* DrawController.h
*
* Created: 08.07.2021 18:36:13
* Author: vhopf
*/


#ifndef __DRAWCONTROLLER_H__
#define __DRAWCONTROLLER_H__

#include "LedCube16x.h"
#include "Base/CyclicModule.h"
#include "Base/IOutputEnableGuard.h"
#include "PlaneOutputWriter.h"
#include "PlaneDataOutputWriter.h"
#include "../FrameBufferController.h"

enum EDrawControllerState{ 
    eIdle,
    eCheckBackBufferReady,
    eLoadPlane,
    eWaitForDataWritten,
    eAdvancePlaneCounter,
    eCompleteBufferWritten
};

class DrawController final : public CyclicModule
{
//variables
public:
protected:
    PlaneOutputWriter * const pPlaneOutputWriter;
    PlaneDataOutputWriter * const pPlaneDataOutputWriter;
    FrameBufferController * const pFrameBufferController;
    IOutputEnableGuard * const pOutputEnableGuard;
    const uint8_t PLANE_DELAY_COUNT;
    

    buffer_t * pFrame;
    uint8_t nPlaneIndex;
    EDrawControllerState eState;
private:

//functions
public:
	DrawController(
            PlaneOutputWriter *pPlaneOutputWriter, 
            PlaneDataOutputWriter *pPlaneDataOutputWriter,
            FrameBufferController *pFrameBufferController,
            IOutputEnableGuard *pOutputEnableGuard,
            uint8_t PLANE_DELAY_COUNT) :
                pPlaneOutputWriter(pPlaneOutputWriter),
                pPlaneDataOutputWriter(pPlaneDataOutputWriter),
                pFrameBufferController(pFrameBufferController),
                pOutputEnableGuard(pOutputEnableGuard),
                PLANE_DELAY_COUNT(PLANE_DELAY_COUNT) {
        eState = EDrawControllerState::eIdle;
    }

    ~DrawController() {
    }

    bool initialize() override;
    void cyclic() override;  
    void reset();
};

#endif //__DRAWCONTROLLER_H__