/*
 * CubeIO.h
 *
 * Created: 02.07.2017 12:12:41
 *  Author: vhopf
 */ 


#pragma once

#ifdef DBG_UNITTEST
#include "../../../MainControllerSharedResources/MockupFunctions.h"
#include "../../../MainControllerSharedResources/TestDeviceDefines.h"
#else
#include "../device/BoardDefines.h"
#endif // DBG_UNITTEST

/* Pin Definitions */
//Column Pins
extern const uint8_t PIN_COL_CLK;
extern const uint8_t PIN_COL_STO;
extern const uint8_t PIN_COL_OE;

//Plane Pins
extern const uint8_t PIN_PLANE_CLK;
extern const uint8_t PIN_PLANE_DATA;
extern const uint8_t PIN_PLANE_OE;
extern const uint8_t PIN_PLANE_STO;

//Data Input Pins
extern const uint8_t PIN_IN_CLK;
extern const uint8_t PIN_IN_SYNC;

//Other
extern const uint8_t PIN_STATUS_PWR_SIG;
extern const uint8_t PIN_STATUS_LED;

/* Port Definitions */
extern volatile uint8_t* PORT_COLUMN;
extern volatile uint8_t* PORT_INPUT;
extern volatile uint8_t* PORT_CONTROL_OUT;
extern volatile uint8_t* PORT_CONTROL_IN;

inline void Device_InitDataDirections(){
	#ifdef DBG_UNITTEST
		TestDevice_InitDataDirections();
	#else
		/* DDR Register Configuration (1=Output Pin, 0=Input Pin) */
		*PORT_COLUMN_DD_ADDR = 0xff;		// Column Port (all output)
		*PORT_INPUT_DD_ADDR = 0x00;		// Input Data Port (all input)
		
		*PORT_CONTROL_OUT_DD_ADDR = 0xff;		// Output Control Port (all outputs)
		*PORT_CONTROL_IN_DD_ADDR = 0b10000000;	// Only PB7 (Stat LED as output)
	#endif
}

inline void Device_InitIOPorts(){
	#ifdef DBG_UNITTEST
		TestDevice_InitIOPorts();
	#else
		*PORT_COLUMN		= 0;
		*PORT_INPUT			= 0;
		*PORT_CONTROL_OUT	= 0;
		*PORT_CONTROL_IN	= 0;
	#endif
}

inline void Cube_OutputEnable(){
	#ifdef DBG_UNITTEST
		TestCube_OutputEnable();
	#else
	*PORT_CONTROL_OUT |= (1<<PIN_COL_OE) | (1<<PIN_PLANE_OE);
	
	//Test led
	*PORT_CONTROL_IN |= (1<<PIN_STATUS_LED);
	#endif
}

inline void Cube_OutputDisable(){
	#ifdef DBG_UNITTEST
		TestCube_OutputDisable();
	#else
	*PORT_CONTROL_OUT &= ~((1<<PIN_COL_OE) | (1<<PIN_PLANE_OE));
	
	//Test led
	*PORT_CONTROL_IN &= ~(1<<PIN_STATUS_LED);
	#endif
}

inline void Cube_TriggerColumnClock(){
	#ifdef DBG_UNITTEST
		TestCube_TriggerColumnClock();
	#else
	//Trigger CLOCK Signal
	*PORT_CONTROL_OUT |= (1<<PIN_COL_CLK); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_COL_CLK); //Low
	#endif
}

inline void Cube_TriggerPlaneClock(){
	#ifdef DBG_UNITTEST
	TestCube_TriggerPlaneClock();
	#else
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_CLK); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_PLANE_CLK); //Low
	#endif
}

inline void Cube_TriggerColumnSto(){
	#ifdef DBG_UNITTEST
	TestCube_TriggerColumnSto();
	#else
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_COL_STO); //High
	//__asm__("nop");
	//__asm__("nop");
	*PORT_CONTROL_OUT &= ~(1<<PIN_COL_STO); //Low
	#endif
}

inline void Cube_TriggerPlaneSto(){
	#ifdef DBG_UNITTEST
	TestCube_TriggerPlaneSto();
	#else
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_STO); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_PLANE_STO); //Low
	#endif
}

inline void Cube_TriggerSto(){
	#ifdef DBG_UNITTEST
	TestCube_TriggerSto();
	#else
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_STO) | (1<<PIN_COL_STO); //High
	*PORT_CONTROL_OUT &= ~((1<<PIN_PLANE_STO) | (1<<PIN_COL_STO)); //Low
	#endif
}