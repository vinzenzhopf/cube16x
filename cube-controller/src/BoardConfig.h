/*
 * BoardConfig.h
 *
 * Created: 02.07.2017 14:02:59
 *  Author: vhopf
 */ 

#ifndef _PORT_DEFINITIONS_
#define _PORT_DEFINITIONS_

#include <avr/io.h>

/* Port Definitions */
#define PORT_COLUMN			PORTC
#define PORT_INPUT			PORTD
#define PORT_CONTROL_OUT	PORTA
#define PORT_CONTROL_IN 	PORTB

/* Pin Definitions */	
//Column Pins	
#define COL_CLK				PA7
#define COL_STO				PA6
#define COL_OE				PA5
//Plane Pins	
#define PLANE_CLK			PA3
#define PLANE_DATA			PA2
#define PLANE_OE			PA1
#define PLANE_STO			PA0
//Data Input Pins	
#define IN_CLK				PB0
#define IN_SYNC				PB1
//Other	
#define STAT_PWR_SIG		PB2
#define STAT_LED			PB7


// uint8_t* PORT_COLUMN              = COL_PORT;
// uint8_t* PORT_INPUT               = IN_PORT;
// uint8_t* PORT_CONTROL_OUT         = CONT_PORT_OUT;
// uint8_t* PORT_CONTROL_IN          = CONT_PORT_IN;

// const uint8_t PIN_COL_CLK         = COL_CLK;
// const uint8_t PIN_COL_STO         =	COL_STO;
// const uint8_t PIN_COL_OE          =	COL_OE;

// const uint8_t PIN_PLANE_CLK       =	PLANE_CLK;
// const uint8_t PIN_PLANE_DATA      =	PLANE_DATA;
// const uint8_t PIN_PLANE_OE        =	PLANE_OE;
// const uint8_t PIN_PLANE_STO       =	PLANE_STO;

// const uint8_t PIN_IN_CLK          =	IN_CLK;
// const uint8_t PIN_IN_SYNC         =	IN_SYNC;

// const uint8_t PIN_STATUS_PWR_SIG  =	STAT_PWR_SIG;
// const uint8_t PIN_STATUS_LED      =	STAT_LED;


inline void Device_InitDataDirections(){
	/* DDR Register Configuration (1=Output Pin, 0=Input Pin) */
	DDRA = 0xff;		// Output Control Port (all outputs)
	DDRB = 0b10000000;	// Only PB7 (Stat LED as output)
	DDRC = 0xff;		// Column Port (all output)
	DDRD = 0x00;		// Input Data Port (all input)
}

inline void Device_InitIOPorts(){
	PORT_COLUMN			= 0;
	PORT_INPUT			= 0;
	PORT_CONTROL_OUT	= 0;
	PORT_CONTROL_IN		= 0;
}

#endif //_PORT_DEFINITIONS_
