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
#include "PlaneOutputWriter.h"
#include "PlaneDataOutputWriter.h"
#include "../FrameBufferController.h"

enum EDrawControllerState{ 
    eIdle,
    eCheckBackBufferReady,
    eInitCubeDrawing,
    eLoadPlane,
    eWaitForDataWritten,
    eWaitForSto,
    eAdvancePlaneCounter
};

class DrawController : public CyclicModule
{
//variables
public:
protected:
    PlaneOutputWriter * const pPlaneOutputWriter;
    PlaneDataOutputWriter * const pPlaneDataOutputWriter;
    FrameBufferController * const pFrameBufferController;
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
        uint8_t PLANE_DELAY_COUNT);
	~DrawController();

    void cyclic() override;  
    void reset();
};

#endif //__DRAWCONTROLLER_H__