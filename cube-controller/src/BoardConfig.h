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
#define PORT_COLUMN				PORTC

#define PORT_INPUT				PORTD

#define PORT_CONTROL_OUT		PORTA
#define PORT_COL_CONTROL		PORTA
#define PORT_PLANE_CONTROL		PORTA

#define PORT_CONTROL_IN 		PORTB
#define PORT_INFO				PORTB

/* Pin Definitions */	
//Column Pins	
#define PIN_COL_CLK				PA7
#define PIN_COL_STO				PA6
#define PIN_COL_OE				PA5
//Plane Pins	
#define PIN_PLANE_CLK			PA3
#define PIN_PLANE_DATA			PA2
#define PIN_PLANE_OE			PA1
#define PIN_PLANE_STO			PA0
//Data Input Pins	
#define PIN_IN_CLK				PB0		//PIN 1
#define PIN_IN_SYNC				PB1		//PIN 2
#define PIN_IN_SPARE1			PB2		//PIN 3
#define PIN_IN_SPARE2			PB3		//PIN 4
//Other	
#define PIN_INFO_PWR_SIG		PB4		//PIN 5
#define PIN_INFO_CYCL_LED		PB5		//PIN 6 - MOSI - LED Green
#define PIN_INFO_DBG_LED		PB6		//PIN 7 - MISO - LED Yellow
#define PIN_INFO_ERR_LED		PB7		//PIN 8 - SCK - LED RED

inline void Device_InitDataDirections(){
	/* DDR Register Configuration (1=Output Pin, 0=Input Pin) */
	DDRA = 0xff;		// Output Control Port (all outputs)
	DDRB = 0b11100000;	// Only PB7,PB6,PB5 (Info LEDs as output)
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
