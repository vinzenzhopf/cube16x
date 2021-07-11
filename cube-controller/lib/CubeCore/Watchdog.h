/*
 * Watchdog.h
 *
 * Created: 10.07.2017 12:59:20
 * Author: Vinzenz hopf (happyfreak.de)
 */ 


#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <LedCube16x.h>
#include <Base/CyclicModule.h>
#include <Base/IOutputEnableGuard.h>


class Watchdog : public CyclicModule, public IOutputEnableGuard {
    protected:
        volatile uint8_t* const PORT_INFO_OUT;
        const uint8_t INFO_CYCLE_PIN;
        const uint8_t INFO_SYSOK_PIN;
        const uint8_t INFO_DBG_PIN;
        volatile uint8_t* const PORT_PLANE_CTL;
        const uint8_t PLANE_OE_PIN;
        volatile uint8_t* const PORT_DATA_CTL;
        const uint8_t DATA_OE_PIN;

        bool bDataReady;
        bool bOutputActive;
        bool bSystemOk;
        
	public:
        Watchdog(
            volatile uint8_t *PORT_INFO_OUT, 
            uint8_t INFO_CYCLE_PIN,
            uint8_t INFO_SYSOK_PIN,
            uint8_t INFO_DBG_PIN,
            volatile uint8_t *PORT_PLANE_CTL,
			uint8_t PLANE_OE_PIN,
			volatile uint8_t *PORT_DATA_CTL,
			uint8_t DATA_OE_PIN);

        virtual void setDataReady(bool bDataReady) override;
        virtual bool isOutputActive();
        virtual bool isSystemOk();

        bool initialize() override;
        void cyclic() override;
    protected:

        void writeInfoLeds();
        void writeOutputEnable();
    private:
};

#endif //__WATCHDOG_H__