#pragma once

#include "../MainControllerTest/MainControllerUnitTests/TestConfig.h"

/* Port Definitions */
#define PORT_COLUMN_ADDR	     (&io_definitions::COL_PORT)
#define PORT_INPUT_ADDR          (&io_definitions::IN_PORT)
#define PORT_CONTROL_OUT_ADDR	 (&io_definitions::CONT_PORT_OUT)
#define PORT_CONTROL_IN_ADDR	 (&io_definitions::CONT_PORT_IN)

/* Port Data Directions */
#define PORT_COLUMN_DD_ADDR      (&io_definitions::COL_PORT_DD)
#define PORT_INPUT_DD_ADDR       (&io_definitions::IN_PORT_DD)
#define PORT_CONTROL_OUT_DD_ADDR (&io_definitions::CONT_PORT_OUT)
#define PORT_CONTROL_IN_DD_ADDR  (&io_definitions::CONT_PORT_IN)

/* Pin Definitions */
//Column Pins
#define COL_CLK			7
#define COL_STO			6
#define COL_OE			5
//Plane Pins
#define PLANE_CLK		3
#define PLANE_DATA		2
#define PLANE_OE		1
#define PLANE_STO		0
//Data Input Pins
#define IN_CLK			0
#define IN_SYNC			1
//Other
#define STAT_PWR_SIG	2
#define STAT_LED		7