/*
 * IOutputEnableGuard.h
 *
 * Created: 10.07.2017 16:31
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

class IOutputEnableGuard
{
    public:
        virtual void setDataReady(bool bDataReady) = 0;
};



