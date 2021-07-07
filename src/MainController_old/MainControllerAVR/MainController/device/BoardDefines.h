/*
 * BoardDefines.h
 *
 * Created: 02.07.2017 19:18:05
 *  Author: vhopf
 */ 

#ifndef _BOARD_DEFINES_H

#include <avr/io.h>

/* Port Definitions */
#define PORT_COLUMN_ADDR	     (&PORTC)
#define PORT_INPUT_ADDR          (&PORTD)
#define PORT_CONTROL_OUT_ADDR	 (&PORTA)
#define PORT_CONTROL_IN_ADDR	 (&PORTB)

/* Port Data Directions */
#define PORT_COLUMN_DD_ADDR      (&DDRC)
#define PORT_INPUT_DD_ADDR       (&DDRD)
#define PORT_CONTROL_OUT_DD_ADDR (&DDRA)
#define PORT_CONTROL_IN_DD_ADDR  (&DDRB)

/* Pin Definitions */
//Column Pins
#define COL_CLK			PA7
#define COL_STO			PA6
#define COL_OE			PA5
//Plane Pins
#define PLANE_CLK		PA3
#define PLANE_DATA		PA2
#define PLANE_OE		PA1
#define PLANE_STO		PA0
//Data Input Pins
#define IN_CLK			PB2
#define IN_SYNC			PB1
//Other
#define STAT_PWR_SIG	PB2
#define STAT_LED		PB7

//Interrupt Vectors
//INT0_vect = PD2, INT1_vect = PD3, INT2_vect = PB2
#define VECT_IN_CLK		INT0_vect
#define VECT_FRAME_UPDATE_TIMER	  TIMER0_COMP_vect

#endif // _BOARD_DEFINES_H