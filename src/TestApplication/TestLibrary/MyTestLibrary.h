/*
 * MyTestLibrary.h
 *
 * Created: 01.07.2017 21:06:30
 *  Author: vhopf
 */ 

#ifndef MYTESTLIBRARY_H_
#define MYTESTLIBRARY_H_

#include <avr/io.h>

extern volatile uint8_t *output_port;

extern volatile uint8_t variable;

inline uint8_t GetVariable(){
	return variable;
}

inline void SetVariable(uint8_t var){
	variable = var;
}

inline void ShiftVariable(){
	variable <<= 1;
}

#endif /* MYTESTLIBRARY_H_ */