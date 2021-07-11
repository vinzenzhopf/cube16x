/*
 * Watchdog.cpp
 *
 * Created: 10.07.2017 12:59:33
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include "Watchdog.h"



Watchdog::Watchdog(
            volatile uint8_t *PORT_INFO_OUT, 
            uint8_t INFO_CYCLE_PIN,
            uint8_t INFO_SYSOK_PIN,
			volatile uint8_t *PORT_PLANE_CTL,
			uint8_t PLANE_OE_PIN,
			volatile uint8_t *PORT_DATA_CTL,
			uint8_t DATA_OE_PIN) :
			PORT_INFO_OUT(PORT_INFO_OUT),
			INFO_CYCLE_PIN(INFO_CYCLE_PIN),
			INFO_SYSOK_PIN(INFO_SYSOK_PIN),
			PORT_PLANE_CTL(PORT_PLANE_CTL),
			PLANE_OE_PIN(PLANE_OE_PIN),
			PORT_DATA_CTL(PORT_DATA_CTL),
			DATA_OE_PIN(DATA_OE_PIN) {
	bOutputActive = false;
	bSystemOk = false;
	bDataReady = false;
}

bool Watchdog::isOutputActive(){
	return bOutputActive;
}

bool Watchdog::isSystemOk(){
	return bSystemOk;
}

void Watchdog::setDataReady(bool bDataReady){
	this->bDataReady = bDataReady;
}

bool Watchdog::initialize(){
	return CyclicModule::initialize();
}

void Watchdog::cyclic(){
	//For Test-Purposes:

	if(bDataReady && bSystemOk){
		bOutputActive = true;
	}else{
		bOutputActive = false;
	}

	writeInfoLeds();
	writeOutputEnable();

	//System is Ready if first cycle has been executed.
	this->bSystemOk = true;
}

void Watchdog::writeInfoLeds(){
	*PORT_INFO_OUT ^= (1<<INFO_CYCLE_PIN); //Toggle Cycle Counter
	if(!bSystemOk){
		*PORT_INFO_OUT |= (1<<INFO_SYSOK_PIN);
	}else{
		*PORT_INFO_OUT &= ~(1<<INFO_SYSOK_PIN);
	}
}
void Watchdog::writeOutputEnable(){
	if(bOutputActive){
		*PORT_PLANE_CTL |= (1<<PLANE_OE_PIN);
		*PORT_DATA_CTL |= (1<<DATA_OE_PIN);
	}else{
		*PORT_PLANE_CTL &= ~(1<<PLANE_OE_PIN);
		*PORT_DATA_CTL &= ~(1<<DATA_OE_PIN);
	}
}