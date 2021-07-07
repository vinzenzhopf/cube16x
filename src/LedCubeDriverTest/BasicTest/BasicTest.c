/*
 * BasicTest.c
 *
 * Created: 22.07.2015 23:00:45
 *  Author: vhopf
 */ 

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


#define sbi(var, bit) ((var) |= (1 << (bit)))
#define cbi(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define tbi(var,bit) ((var) ^= (1 << (bit)))

#define DATAPORT PORTD
#define CONTROLPORT PORTC

#define CONT_CLK PC0
#define CONT_STO PC1
#define CONT_OE PC2

volatile uint8_t data;

void writeFrame(){
	for(uint8_t i = 0; i < 32; i++){
		if(i%4==0)
			DATAPORT = data;
		else
			DATAPORT = ~data;
			
		sbi(CONTROLPORT, CONT_CLK);
		_delay_us(2);
		cbi(CONTROLPORT, CONT_CLK);
		_delay_us(2);
	}
	sbi(CONTROLPORT, CONT_STO);
	_delay_us(2);
	cbi(CONTROLPORT, CONT_STO);
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0b111;
		
	sbi(CONTROLPORT, CONT_OE);
	
	uint16_t t = 0;
	while(1)
	{
		if(++t > 10000){
			t = 0;
			data = ~data;
		}
		writeFrame();
		_delay_us(10);
	}
}