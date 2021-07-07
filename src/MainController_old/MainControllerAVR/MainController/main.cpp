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

void InitExtInterrupt();
void InitTimer();

volatile uint8_t tim0_cnt = 0;

int main(void)
{
	Device_InitDataDirections();
	Device_InitIOPorts();
	
	Cube_InitDataBuffer();
	//Setup TestBuffer
	
	InitExtInterrupt();
	InitTimer();
	
// 	uint8_t planeIdx = 0;
//     while (1) 
//     {
// 		
// 		Cube_WritePlane(planeIdx);		
// 		
// 		++planeIdx;
// 		planeIdx %= PLANE_COUNT;
// 		_delay_ms(40);
//     }


	bDoSth = 0;
	bStatus = 0;
	sei();

	while(1){
		
		
		
		
		if(bDoSth == 1){
			*PORT_CONTROL_IN ^= (1<<PIN_STATUS_LED);
			bDoSth = 0;
		}
		
	}
	
}

void InitExtInterrupt(){
	//External Interrupt
	
	//MCU Control- and Status Register
	MCUCSR |= (1<<ISC2); //Trigger ExtINT2 on rising edge	
	//MCUCSR |= (0<<ISC2); //Trigger ExtINT2 on falling edge
	
	//General Interrupt Control Register - Enable External Interrupt 2 Request
	GICR |= (1<<INT2);
	
	//Activate internal Pullupresistor of PB2
	*PORT_CONTROL_IN |= (1<<IN_CLK); //PORTB |= (1<<PB2)
		
}

void InitTimer(){
	//Timer 0
	
	//Waveform Generation
	TCCR0 |= (1<<WGM01) | (0<<WGM00); //Timer in CTC mode: Timer-Count 0-OCR0
	//OCR0 = 124; //CTC-Mode Compare Register -> 2kHz
	OCR0 = 250; //CTC-Mode Compare Register -> 1kHz
	
	TCCR0 |= (0<<COM01) | (0<<COM00); //External Pin disconnected
	
	//Prescaler Settings
	//TCCR0 |= (0<<CS02) | (1<<CS01) | (0<<CS00); // clk_io/8
	TCCR0 |= (0<<CS02) | (1<<CS01) | (1<<CS00); // clk_io/64
	//TCCR0 |= (1<<CS02) | (0<<CS01) | (0<<CS00); // clk_io/256
	//TCCR0 |= (1<<CS02) | (0<<CS01) | (1<<CS00); // clk_io/1024
	
	TIMSK |= (1<<OCIE0); //Enable Output Compare Match Interrupt
}
 
ISR(TIMER0_COMP_vect){
	cli();
	++tim0_cnt;
	sei();
}



ISR(INT2_vect){
	//cli();
	//*PORT_CONTROL_IN ^= (1<<PIN_STATUS_LED);
	//sei();
}


