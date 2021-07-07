/*
 * CubeLogic.h
 *
 * Created: 01.07.2017 12:23:42
 * Author: Vinzenz Hopf (happyfreak.de)
 */


#pragma once

#include "CubeIO.h"
#include "CubeFrameBuffer.h"


/************************************************************************/
/* Loops through the plane data and writes it with 8 bits parallel to   */
/* the driver boards.                                                   */
/*                                                                      */
/* Each Plane in the buffer consists of 32 Bytes of data.               */
/* Each of the 8 driver-shift-register-chains is connected to one bit   */
/* of the output port COL_PORT. So, for example: The first Bit of the   */
/* COL_PORT is loaded and clocked 32 times with the data of the first   */
/* 32 bits in the Plane-Array. This contains the Data for 2 Rows of the */
/* Plane on the Cube.                                                   */
/************************************************************************/
void Cube_WritePlaneData(uint8_t planeIdx);

/************************************************************************/
/* Writes the plane index to the PlaneDriver outputs.                   */
/* Operates the Jonson-Counter on the PlaneDriver.                      */
/************************************************************************/
void Cube_WritePlaneCounter(uint8_t planeIdx);

/************************************************************************/
/* Writes the Plane data in the Shift registers and sets the            */
/* Plane-driver counter to the next plane.                              */
/************************************************************************/
inline void Cube_WritePlane(uint8_t planeIdx){
	Cube_WritePlaneData(planeIdx);
	Cube_WritePlaneCounter(planeIdx);
 
 
	//Pulse store signal and store all the preloaded Data in the Latches.
	Cube_TriggerSto();
}