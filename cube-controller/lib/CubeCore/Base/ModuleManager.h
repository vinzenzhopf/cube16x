/*
 * ModuleManager.h
 *
 * Created: 08.07.2017 22:39:5
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#pragma once

#include "CyclicModule.h"
#include "IModuleWatchdog.h"

enum class EModuleManagerState{
    None,
    Initialize,
    Running
};

class ModuleManager {
    //Variables
    private:
        IModuleWatchdog * const pModuleWatchdog;

        CyclicModule* arrModules[MAX_MODULE_COUNT];
        uint8_t nModuleCount;

        EModuleManagerState eState;

    //Methods
    public:
        ModuleManager(
            IModuleWatchdog *pModuleWatchdog) :
                pModuleWatchdog(pModuleWatchdog), 
                nModuleCount(0),
                eState(EModuleManagerState::Initialize) {
        }
	    virtual ~ModuleManager() = default;

        /**
         * Registers a module for cyclic execution
         */
        void registerModule(CyclicModule* module){
            arrModules[nModuleCount] = module;
            nModuleCount++;
        }

        /**
         * Calls every startup method on its registered modules.
         * Startup initializsations. Initialization order must be resprected here. 
         * Should only be used for code, that is blocking and cannot be spreaded over cycles.
         */
        void setup(){
            for(uint8_t i = 0; i < nModuleCount; i++){
                arrModules[i]->setup();
            }
        }

        /**
         * Method that should be called cyclic and contain the main procedure logic of this module.
         */
        void cyclic(){
            switch (eState)
            {
            case EModuleManagerState::None:
                eState = EModuleManagerState::Initialize;
                break;
            
            case EModuleManagerState::Initialize:
                {
                    bool bInitialized = true;
                    for(uint8_t i = 0; i < nModuleCount; i++){
                        if(!arrModules[i]->initialize()){
                            bInitialized = false;
                        }
                    }
                    if(bInitialized){
                        eState = EModuleManagerState::Running;
                    }
                }
                break;

            case EModuleManagerState::Running:
                {
                    bool bAllModulesOk = true;
                    for(uint8_t i = 0; i < nModuleCount; i++){
                        arrModules[i]->cyclic();
                        bAllModulesOk = bAllModulesOk && arrModules[i]->bModuleOk;
                    }
                    pModuleWatchdog->setModulesOk(bAllModulesOk);
                }
                break;

            default:
                eState = EModuleManagerState::None;
                break;
            }
        }    

        bool isInitialized(){
            return eState == EModuleManagerState::Running;
        }

    protected:
};

