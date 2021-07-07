/*
 * PowerBoard.c
 *
 * Created: 15.04.2016 17:14:54
 * Author : vhopf
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define sbi(port,bit)	(port) |= (1 << (bit))
#define cbi(port,bit)	(port) &= ~(1<<(bit))

/* DDR Register Configuration (1=Output Pin, 0=Input Pin) */
#define DIR_C		0b00000001		// 
#define DIR_D		0b11000010		// Input Data Port


#define STATE_OFF				0
#define STATE_ON				1
#define STATE_SWITCHED_OFF		2

#define TRANSITION_NONE         0
#define TRANSITION_RISING_EDGE  1
#define TRANSITION_FALLING_EDGE 2

volatile uint8_t state = STATE_OFF;
//volatile uint8_t transition = TRANSITION_NONE;

#define BTN_DEAD_CYCLES 20

#define BTN_FALLING_EDGE	1
#define BTN_RISING_EDGE		2
#define BTN_STATE_ON		3
#define BTN_STATE_OFF		4


volatile uint8_t lastPWRSWState = 0;
volatile uint8_t debounceCycleCnt = 0;
volatile uint8_t deadCycleCnt = 0;

uint8_t checkPWR_SW(){
	//Read Input from switch
	uint8_t curPWRSWState = ((PIND & (1<<PIND2))>>PIND2);
	
	if(deadCycleCnt==0){
	
		if(curPWRSWState && !lastPWRSWState){
			//Falling edge
			lastPWRSWState = curPWRSWState;
			deadCycleCnt = BTN_DEAD_CYCLES;
			return TRANSITION_FALLING_EDGE;
		}else if(!curPWRSWState && lastPWRSWState){
			//Rising edge
			lastPWRSWState = curPWRSWState;
			deadCycleCnt = BTN_DEAD_CYCLES;
			return TRANSITION_RISING_EDGE;
		}
	}else{
		deadCycleCnt--;
	}
	return TRANSITION_NONE;
}

void switchOn(){
	 PORTD |= (1<<PORTD7); //HIGH on green LED
	 PORTC &= ~(1<<PORTC0); //LOW on Relais
}

void switchOff(){
	PORTD &= ~(1<<PORTD7); //LOW on green LED
	PORTC |= (1<<PORTC0); //HIGH on Relais
}

int main(void)
{
	PORTD = 0;
	PORTC = 0b00000001;
	
	//Initialize Ports
	DDRD = DIR_D;
	DDRC = DIR_C;
	
	
	
	while (1) 
    {
		uint8_t transition = checkPWR_SW();
		
		switch(state){
			case STATE_ON:
				if(transition==TRANSITION_RISING_EDGE){
					PORTD |= (1<<PORTD6); //HIGH on red LED
					_delay_ms(200);
					PORTD &= ~(1<<PORTD6); //LOW on red LED
					state = STATE_SWITCHED_OFF;
				}
				break;
			case STATE_OFF:
				if(transition==TRANSITION_RISING_EDGE){
					switchOn();
					state = STATE_ON;
				}
				break;
			case STATE_SWITCHED_OFF:
				//Wait for the PI to shut down.
				switchOff();
				state = STATE_OFF;
				break;
		}
		_delay_ms(2);
    }
}


