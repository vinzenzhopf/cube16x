/*
 * TestApplication.cpp
 *
 * Created: 01.07.2017 20:24:32
 * Author : vhopf
 */ 

#define F_CPU 16000000l

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "MyTestLibrary.h"
//#include "TestClass.h"
//#include <libTestLibrary/TestClass.h>

volatile uint8_t *output_port = &PORTB;
volatile uint8_t variable;

class Rectangle2 {
	int width, height;
	public:
	void set_values (int x, int y) {
		width = x;
		height = y;
	}
	int area() {return width*height;}
} rect2;

TestClass test;

int main(void)
{
	variable = 1;
	
    /* Replace with your application code */
    while (1) 
    {
		for(uint8_t i = 0; i < 8; i++){
			*output_port = GetVariable();
			ShiftVariable();
			//rect.set_values (3,4);
			rect2.set_values (3,4);
			_delay_ms(1000);	
		}
    }
}
