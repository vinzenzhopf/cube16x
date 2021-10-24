/*
 * CyclicModule.cpp
 *
 * Created: 08.07.2017 19:45:45
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include "CyclicModule.h"

CyclicModule::CyclicModule() :
    nCycleDelay(0) {
}

/**
 * Method for Module initialization, if the module is depending on other stuff to be initialized. 
 * Once all initialize calls are finished (returning true) then cyclic starts to get called.
 * @returns bool true, when the initialize method is finished.
 */
bool CyclicModule::initialize(){
    return true;
}

/**
 * Method that should be called cyclic and contain the main procedure logic of this module.
 */
void CyclicModule::cyclic(){
}

/**
 * Can be called and waits in a cyclic, non blocking mannor until the
 * timeout is expired.                                                 
 */
bool CyclicModule::waitCycleTimeout(uint16_t nDelay){
    nCycleDelay++;
    if(nCycleDelay > nDelay){
        nCycleDelay = 0;
        return true;
    }
    return false;
}

/**
 * Resets the cyclic Timeout function
 */
void CyclicModule::resetCycleTimeout(){
    nCycleDelay = 0;
}