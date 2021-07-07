/*
 * CubeLogic.cpp
 *
 * Created: 01.07.2017 17:25:32
 * Author: Vinzenz Hopf (happyfreak.de)
 */

 #include <avr/io.h>
 #include "CubeIO.h"
 #include "CubeFrameBuffer.h"
 #include "CubeLogic.h"

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
 void Cube_WritePlaneData(uint8_t planeIdx){
	 uint8_t output;
	 //Cycle through the 32 serial loading actions
	 for(uint8_t cycle = 0; cycle < 32; cycle++){
 
		 //Building the output by iterating the plane with word_t (32bit)
		 //steps and shifting the next bit in the output.
		 output = 0;
 
		 for(uint8_t offset = 0; offset < 8; offset++) {
			 output <<=1;
			 const word_t mask(1<<cycle);
			 output |= ((outputBuffer->asPlanes[planeIdx].asWords[offset] & mask) >> cycle);
		 }
 
		 //Write Output
		 *PORT_COLUMN = output;
		 Cube_TriggerColumnClock();
	 }
 }

 /************************************************************************/
 /* Writes the plane index to the PlaneDriver outputs.                   */
 /* Operates the Jonson-Counter on the PlaneDriver.                      */
 /************************************************************************/
 void Cube_WritePlaneCounter(uint8_t planeIdx){
	 // Shifting the Plane Ring Counter
	 if(planeIdx == 0){
		//Sets the first bit (every 16th cycle)
		 *PORT_CONTROL_OUT |= (1<<PIN_PLANE_DATA); //High
		 Cube_TriggerPlaneClock(); //TODO Optimize
	 } else {
		 *PORT_CONTROL_OUT &= ~(1<<PIN_PLANE_DATA); //Low
		 Cube_TriggerPlaneClock();
	 }
 }