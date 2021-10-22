/*
 * ModuleManager.cpp
 *
 * Created: 08.07.2017 22:38:52
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include "ModuleManager.h"

ModuleManager::ModuleManager(){
    nModuleCount = 0;
    eState = EModuleManagerState::Initialize;
}

ModuleManager::~ModuleManager(){
}

/**
 * Registers a module for cyclic execution
 */
void ModuleManager::registerModule(CyclicModule* module){
    arrModules[nModuleCount] = module;
    nModuleCount++;
}

/**
 * Method that should be called cyclic and contain the main procedure logic of this module.
 */
void ModuleManager::cyclic(){
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
            for(uint8_t i = 0; i < nModuleCount; i++){
                arrModules[i]->cyclic();
            }
        }
        break;

    default:
        eState = EModuleManagerState::None;
        break;
    }
}

bool ModuleManager::isInitialized(){
    return eState == EModuleManagerState::Running;
}