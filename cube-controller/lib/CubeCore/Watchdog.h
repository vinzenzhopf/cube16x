/*
 * Watchdog.h
 *
 * Created: 10.07.2017 12:59:20
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include <LedCube16x.h>
#include <Base/CyclicModule.h>
#include <Base/IOutputEnableGuard.h>


class Watchdog final : public CyclicModule, public IOutputEnableGuard {
    protected:
        const uint8_t INFO_CYCLE_PIN;
        const uint8_t INFO_SYSOK_PIN;
        const uint8_t INFO_SYSERR_PIN;
        const uint8_t INFO_DBG_PIN;
        const uint8_t OE_PIN;
        const uint32_t TARGET_CYCLE_TIME_US;

        bool bDataReady;
        bool bOutputActive;
        bool bSystemOk;
        bool bCycleTimeExceeded;

        uint32_t cycleStartTicks;
        uint32_t lastCycleTime;
        
	public:
        Watchdog(
                uint8_t INFO_CYCLE_PIN,
                uint8_t INFO_SYSOK_PIN,
                uint8_t INFO_SYSERR_PIN,
                uint8_t INFO_DBG_PIN,
                uint8_t OE_PIN,
                uint32_t TARGET_CYCLE_TIME_US) :  
                    INFO_CYCLE_PIN(INFO_CYCLE_PIN),
                    INFO_SYSOK_PIN(INFO_SYSOK_PIN),
                    INFO_SYSERR_PIN(INFO_SYSERR_PIN),
                    INFO_DBG_PIN(INFO_DBG_PIN),
                    OE_PIN(OE_PIN),
                    TARGET_CYCLE_TIME_US(TARGET_CYCLE_TIME_US),
                    bDataReady(false),
                    bOutputActive(false),
                    bSystemOk(false),
                    bCycleTimeExceeded(false) {
        }
        ~Watchdog() = default;

        void setDataReady(bool bDataReady) override{
            this->bDataReady = bDataReady;
        }

        bool isOutputActive(){
            return bOutputActive;
        }
        bool isSystemOk(){
            return bSystemOk;
        }
        bool isCycleTimeExceeded(){
            return bCycleTimeExceeded;
        }

        bool initialize() override{
            return true;
        }

        void cyclic() override{
            //For Test-Purposes:

            bOutputActive = bDataReady && bSystemOk;

            writeInfoLeds();
            writeOutputEnable();

            //System is Ready if first cycle has been executed.
            this->bSystemOk = false;

            //Reset CycleTimeExceeded marker
            this->bCycleTimeExceeded = false;
        }
        
        inline void initCycle() {
            digitalWriteFast(INFO_CYCLE_PIN, HIGH);
            this->cycleStartTicks = micros();
        }

        inline void adjustCycleTime() {
            digitalWriteFast(INFO_CYCLE_PIN, LOW);
            uint32_t cycleTimeCurrent = micros() - cycleStartTicks;
            this->lastCycleTime = cycleTimeCurrent;

            // if(serialDebug){
            //     Serial.printf("Last:%d Excceded:%d SystemOk:%d\n", lastCycleTime, bCycleTimeExceeded, bSystemOk);

            //     uint32_t cycleTimeCurrent = micros() - cycleStartTicks;
            //     this->lastCycleTime = cycleTimeCurrent;
            // }

            if(cycleTimeCurrent > TARGET_CYCLE_TIME_US){
                bCycleTimeExceeded = true;
            }else{
                while(cycleTimeCurrent < TARGET_CYCLE_TIME_US){
                    asm volatile("nop\n\t""nop\n\t""nop\n\t""nop\n\t");
                    cycleTimeCurrent = micros() - cycleStartTicks;
                }
            }
        }

    protected:
        void writeInfoLeds() {
            //digitalToggleFast(INFO_CYCLE_PIN);
            digitalWriteFast(INFO_SYSOK_PIN, bSystemOk);
            //digitalWriteFast(INFO_SYSERR_PIN, bCycleTimeExceeded);
            digitalWriteFast(INFO_DBG_PIN, bDataReady);
        }
        void writeOutputEnable() {
            digitalWriteFast(OE_PIN, bOutputActive);
        }
    private:
};

