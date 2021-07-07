/*
 * MainController.cpp
 *
 * Created: 02.07.2017 12:11:32
 * Author : vhopf
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "device/BoardDefines.h"
#include "lib/CubeIO.h"
#include "lib/CubeFrameBuffer.h"
#include "lib/CubeLogic.h"


int main(void)
{
	Device_InitDataDirections();
	Device_InitIOPorts();
	
	Cube_InitDataBuffer();
	//Setup TestBuffer
	
	uint8_t planeIdx = 0;
    while (1) 
    {
		
		Cube_WritePlane(planeIdx);		
		
		++planeIdx;
		planeIdx %= PLANE_COUNT;
		_delay_ms(40);
    }
}

