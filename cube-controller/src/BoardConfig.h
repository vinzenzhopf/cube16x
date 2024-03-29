/*
 * BoardConfig.h
 *
 * Created: 02.07.2017
 * Author: vhopf
 */ 

#pragma once

#include "CubeCore.h"

#include "TeensyUtils.h"
#include "IPAddress.h"

/* Pin Definitions */	
//0-7 		Plane Data Pins
//8-9		Plane Control Pins
//10		Row Data Pin
//11-12		Row Control Pins

//Output Enable Pin
#define PIN_OE					41

//Column Pins	
#define PIN_COL_DATA0			0		//Data Start Pin 0-7	
#define PIN_COL_CLK				8
#define PIN_COL_STO				9

//Plane Pins	
#define PIN_PLANE_DATA			10
#define PIN_PLANE_CLK			11
#define PIN_PLANE_STO			12

//Other	
#define PIN_INFO_CYCL_LED		30		//PIN 6 - MOSI - LED Green
#define PIN_INFO_DBG_LED		31		//PIN 7 - MISO - LED Yellow
#define PIN_INFO_PWR_SIG		32		//PIN 5
#define PIN_INFO_ERR_LED		40		//PIN 8 - SCK - LED RED

#define PIN_DEBUG_SWITCH		23		
#define PIN_STATUS_LED_R		14
#define PIN_STATUS_LED_G		15
#define PIN_STATUS_LED_B		18

#define CYCLE_TIME_US			5	
#define ANIMATION_FRAMERATE    	60
#define ANIMATION_FRAME_TIME_US	( 1 / ANIMATION_FRAMERATE )*1000*1000

byte MacAddress[] = { 0x02, 0xBE, 0xFD, 0xF6, 0x7C, 0xCD };
IPAddress DefaultIp(192, 168, 1, 177);
IPAddress DefaultDns(192, 168, 1, 1);
IPAddress DefaultGateway(192, 168, 1, 1);
IPAddress DefaultSubnet(255, 255, 255, 0);
int ServerPort = 4242;

inline void BoardInitDataDirections(){
	//Columns
	for(int i = 0; i < 8; i++){
		pinMode(PIN_COL_DATA0+i, OUTPUT);	
	}
	pinMode(PIN_OE, OUTPUT);
	pinMode(PIN_COL_CLK, OUTPUT);
	pinMode(PIN_COL_STO, OUTPUT);

	//Planes
	pinMode(PIN_PLANE_DATA, OUTPUT);
	pinMode(PIN_PLANE_CLK, OUTPUT);
	pinMode(PIN_PLANE_STO, OUTPUT);

	//LEDs
	pinMode(PIN_DEBUG_SWITCH, INPUT);
	pinMode(PIN_INFO_DBG_LED, OUTPUT);
	pinMode(PIN_INFO_PWR_SIG, OUTPUT);
	pinMode(PIN_INFO_ERR_LED, OUTPUT);

	pinMode(PIN_INFO_CYCL_LED, OUTPUT);
	pinMode(PIN_STATUS_LED_R, OUTPUT);
	pinMode(PIN_STATUS_LED_G, OUTPUT);
	pinMode(PIN_STATUS_LED_B, OUTPUT);
}

inline void BoardInitIOPorts(){
	//Columns
	digitalWriteByte(PIN_COL_DATA0, 0);
	digitalWriteFast(PIN_OE, 0);
	digitalWriteFast(PIN_COL_CLK, 0);
	digitalWriteFast(PIN_COL_STO, 0);

	//Planes
	digitalWriteFast(PIN_PLANE_DATA, 0);
	digitalWriteFast(PIN_PLANE_CLK, 0);
	digitalWriteFast(PIN_PLANE_STO, 0);

	//LEDs
	digitalWriteFast(PIN_INFO_CYCL_LED, 0);
	digitalWriteFast(PIN_INFO_DBG_LED, 0);
	digitalWriteFast(PIN_INFO_PWR_SIG, 0);
	digitalWriteFast(PIN_INFO_ERR_LED, 0);

	analogWrite(PIN_INFO_DBG_LED, 0);
	analogWrite(PIN_INFO_PWR_SIG, 0);
	analogWrite(PIN_INFO_ERR_LED, 0);
}
