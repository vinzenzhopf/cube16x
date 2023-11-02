/*
 * CyclicModule.h
 *
 * Base Class for all Modules that have to be called in a cyclic mannor.
 *
 *
 * Created: 08.07.2017 19:45:57
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"

class CyclicModule {
    //Variables
    private:	
        uint16_t nCycleDelay;
	
    //Methods
    public:
        CyclicModule();
	    ~CyclicModule() = default;

        /**
         * Public variable to forward error states or other unsafe states to the watchdog.
         */
        bool bModuleOk = true;

        /**
         * Startup initializsations. Initialization order must be resprected here. 
         * Should only be used for code, that is blocking and cannot be spreaded over cycles.
         */
        virtual void setup() {
        }

        /**
         * Method for Module initialization, if the module is depending on other stuff to be initialized. 
         * Once all initialize calls are finished (returning true) then cyclic starts to get called.
         * @returns bool When the initialize method is finished.
         */
        virtual bool initialize() = 0;

        /**
         * Method that should be called cyclic and contain the main procedure logic of this module.
         */
        virtual void cyclic() = 0;

    protected:
        /**
         * Can be called and waits in a cyclic, non blocking mannor until the
         * timeout is expired.                                                 
         */
        bool waitCycleTimeout(uint16_t nDelay);

        /**
         * Resets the cyclic Timeout function
         */
        void resetCycleTimeout();
};

