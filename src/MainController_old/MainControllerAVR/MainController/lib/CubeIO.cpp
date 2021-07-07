/*
 * CubeIO.cpp
 *
 * Created: 02.07.2017 20:04:32
 *  Author: vhopf
 */ 


#include <inttypes.h>
#include "CubeIO.h"

/* Pin Definitions */
//Column Pins
const uint8_t PIN_COL_CLK         = COL_CLK;
const uint8_t PIN_COL_STO         =	COL_STO;
const uint8_t PIN_COL_OE          =	COL_OE;

//Plane Pins
const uint8_t PIN_PLANE_CLK       =	PLANE_CLK;
const uint8_t PIN_PLANE_DATA      =	PLANE_DATA;
const uint8_t PIN_PLANE_OE        =	PLANE_OE;
const uint8_t PIN_PLANE_STO       =	PLANE_STO;

//Data Input Pins
const uint8_t PIN_IN_CLK          =	IN_CLK;
const uint8_t PIN_IN_SYNC         =	IN_SYNC;

//Other
const uint8_t PIN_STATUS_PWR_SIG  =	STAT_PWR_SIG;
const uint8_t PIN_STATUS_LED      =	STAT_LED;

/* Port Definitions */
volatile uint8_t* PORT_COLUMN      = PORT_COLUMN_ADDR;
volatile uint8_t* PORT_INPUT       = PORT_INPUT_ADDR;
volatile uint8_t* PORT_CONTROL_OUT = PORT_CONTROL_OUT_ADDR;
volatile uint8_t* PORT_CONTROL_IN  = PORT_CONTROL_IN_ADDR;

