/*
 * LedCubeDriverTest.c
 *
 * Created: 20.07.2015 13:20:05
 *  Author: vhopf
 */ 

#include <avr/io.h>
#define F_CPU 8000000

union frame{
	uint8_t asBytes[32];
	uint32_t asInt[8];	
};

#define sbi(var, bit) ((var) |= (1 << (bit)))
#define cbi(var, bit) ((var) &= (unsigned)~(1 << (bit)))
#define tbi(var,bit) ((var) ^= (1 << (bit)))

#define DATAPORT PORTD
#define CONTROLPORT PORTC

#define CONT_CLK PC0
#define CONT_STO PC1
#define CONT_OE PC2

//volatile uint8_t currentFrame[32];
union frame currentFrame;
//length = 32 --> 256 bits
//8*32 -> 2 bytes a row, 4 bytes per driver channel

void setDataport(uint8_t offset){
	uint8_t out = 0b0;
	for(uint8_t i = 0; i <8; i++){
		out |= (((currentFrame.asInt[i]>>offset) & 1) << i);
	}	
	DATAPORT = out;
}	

void writeFrame(){
	for(uint8_t i = 0; i < 32; i++){
		setDataport(i);
		sbi(CONTROLPORT, CONT_CLK);
		cbi(CONTROLPORT, CONT_CLK);
	}
	sbi(CONTROLPORT, CONT_STO);
	cbi(CONTROLPORT, CONT_STO);
}

void shiftFrame(){
	for(uint8_t i = 0; i < 32; i++){
		uint8_t t = (currentFrame.asBytes[i]&(1<<7))>0;
		currentFrame.asBytes[i] <<= 1;
		currentFrame.asBytes[i] |= t;
	}
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0b111;
	
	uint8_t d = 0x1;
	for(uint8_t i = 0; i < 32; i++){
		currentFrame.asBytes[i] = d;
	}
	
	sbi(CONTROLPORT, CONT_OE);
	
	uint16_t t = 0;
    while(1)
    {
		if(++t > 100){
			t = 0;
			shiftFrame();
		}
		writeFrame();
    }
}