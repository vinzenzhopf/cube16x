/*
 * ModuleManager.h
 *
 * Created: 08.07.2017 22:39:5
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 


#ifndef __MODULEMANAGER_H__
#define __MODULEMANAGER_H__

#include "CyclicModule.h"

#define MODULE_COUNT 10

enum class EModuleManagerState{
    None,
    Initialize,
    Running
};

class ModuleManager {
    //Variables
    private:	
        CyclicModule* arrModules[MODULE_COUNT];
        uint8_t nModuleCount;

        EModuleManagerState eState;

    //Methods
    public:
        ModuleManager();
	    ~ModuleManager();

        /**
         * Registers a module for cyclic execution
         */
        void registerModule(CyclicModule* module);

        /**
         * Method that should be called cyclic and contain the main procedure logic of this module.
         */
        void cyclic();    

        bool isInitialized();

    protected:
};

#endif //__MODULEMANAGER_H__