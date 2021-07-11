/*
 * IOutputEnableGuard.h
 *
 * Created: 10.07.2017 16:31
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __IOUTPUTENABLEGUARD_H__
#define __IOUTPUTENABLEGUARD_H__

class IOutputEnableGuard
{
    public:
        virtual void setDataReady(bool bDataReady) = 0;
};

#endif //__IOUTPUTENABLEGUARD_H__

