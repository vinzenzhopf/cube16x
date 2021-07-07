/*
 * CubeIO.h
 *
 * Created: 02.07.2017 12:12:41
 *  Author: vhopf
 */ 


#pragma once

extern const uint8_t PIN_COL_CLK;
extern const uint8_t PIN_COL_STO;
extern const uint8_t PIN_COL_OE;

extern const uint8_t PIN_PLANE_CLK;
extern const uint8_t PIN_PLANE_DATA;
extern const uint8_t PIN_PLANE_OE;
extern const uint8_t PIN_PLANE_STO;

extern const uint8_t PIN_IN_CLK;
extern const uint8_t PIN_IN_SYNC;

extern const uint8_t PIN_STATUS_PWR_SIG;
extern const uint8_t PIN_STATUS_LED;

extern uint8_t* PORT_COLUMN;
extern uint8_t* PORT_INPUT;
extern uint8_t* PORT_CONTROL_OUT;
extern uint8_t* PORT_CONTROL_IN;

extern void Device_InitDataDirections();
extern void Device_InitIOPorts();


inline void Cube_OutputEnable(){
	*PORT_CONTROL_OUT |= (1<<PIN_COL_OE) | (1<<PIN_PLANE_OE);
	
	//Test led
	*PORT_CONTROL_IN |= (1<<PIN_STATUS_LED);
}

inline void Cube_OutputDisable(){
	*PORT_CONTROL_OUT &= ~((1<<PIN_COL_OE) | (1<<PIN_PLANE_OE));
	
	//Test led
	*PORT_CONTROL_IN &= ~(1<<PIN_STATUS_LED);
}

inline void Cube_TriggerColumnClock(){
	//Trigger CLOCK Signal
	*PORT_CONTROL_OUT |= (1<<PIN_COL_CLK); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_COL_CLK); //Low
}

inline void Cube_TriggerPlaneClock(){
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_CLK); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_PLANE_CLK); //Low
}

inline void Cube_TriggerColumnSto(){
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_COL_STO); //High
	//__asm__("nop");
	//__asm__("nop");
	*PORT_CONTROL_OUT &= ~(1<<PIN_COL_STO); //Low
}

inline void Cube_TriggerPlaneSto(){
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_STO); //High
	*PORT_CONTROL_OUT &= ~(1<<PIN_PLANE_STO); //Low
}

inline void Cube_TriggerSto(){
	//Trigger STO Signal
	*PORT_CONTROL_OUT |= (1<<PIN_PLANE_STO) | (1<<PIN_COL_STO); //High
	*PORT_CONTROL_OUT &= ~((1<<PIN_PLANE_STO) | (1<<PIN_COL_STO)); //Low
}
