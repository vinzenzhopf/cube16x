/*
 * IModuleWatchdog.h
 *
 * Created: 02.11.2023 15:31
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

class IModuleWatchdog
{
    public:
        virtual void setModulesOk(bool bModulesOk) = 0;
};
