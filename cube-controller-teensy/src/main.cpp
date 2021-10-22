#include <Arduino.h>
#include "BoardConfig.h"
#include "Base/ModuleManager.h"
#include "Watchdog.h"
#include "FrameBuffer.h"
#include "FrameBufferController.h"
#include "Drawing/PlaneDataOutputWriter.h"
#include "Drawing/PlaneOutputWriter.h"
#include "Drawing/DrawController.h"

ModuleManager moduleManager;
Watchdog watchdog(
    PIN_INFO_CYCL_LED,          //INFO_CYCLE_PIN
    PIN_INFO_PWR_SIG,           //INFO_SYSOK_PIN
    PIN_INFO_ERR_LED,           //INFO_SYSERR_PIN
    PIN_INFO_DBG_LED,           //INFO_DBG_PIN
    PIN_OE,                     //PLANE_OE_PIN
    CYCLE_TIME_US               //TARGET_CYCLE_TIME_US
);
FrameBufferController frameBufferController;
PlaneOutputWriter planeOutputWriter(
    PIN_PLANE_CLK, 
    PIN_PLANE_STO,
    PIN_PLANE_DATA,
    0
);
PlaneDataOutputWriter planeDataOutputWriter(
    PIN_COL_CLK, 
    PIN_COL_STO,
    PIN_COL_DATA0,
    0
);
DrawController drawController(
    &planeOutputWriter, 
    &planeDataOutputWriter,
    &frameBufferController,
    &watchdog,
    10
);

FrameBuffer bufferAlternating, bufferFull, bufferEmpty;

void WriteTestBuffer(buffer_t *pBuffer){
    const uint16_t data = 0b1000000010000000;
    for(uint8_t p = 0; p < 16; p++){
        for(uint8_t r = 0; r < 16; r++){
            pBuffer->asPlanes[p].asShort[r] = data;
        }
    }
}

void setup() {
    BoardInitIOPorts();
    BoardInitDataDirections();

    //Set ErrorLED to HIGH during initializaton
    digitalWriteFast(PIN_INFO_ERR_LED, HIGH);

    moduleManager.registerModule(&watchdog);
    moduleManager.registerModule(&frameBufferController);
    moduleManager.registerModule(&planeOutputWriter);
    moduleManager.registerModule(&planeDataOutputWriter);
    moduleManager.registerModule(&drawController);

    bufferAlternating.setBufferAlternating();
    bufferFull.setBuffer();
    bufferEmpty.clearBuffer();

    // FrameBuffer bufferTest;
    // // bufferTest.clearBuffer();
    // WriteTestBuffer(bufferTest.getBuffer());
    // uint8_t i = 200;
    // bool bAlternating = false;
}

void loop() {

    watchdog.initCycle();

    moduleManager.cyclic();
    if(moduleManager.isInitialized() && frameBufferController.isFrontBufferReady()){
        // i++;
        // if(i > 200){
        //     if(bAlternating){
        //         frameBufferController.copyBuffer(bufferEmpty.getBuffer());  
        //     }else{
        //         frameBufferController.copyBuffer(bufferFull.getBuffer());  
        //     }
        //     bAlternating = !bAlternating;
        //     i = 0;
        // }
        frameBufferController.copyBuffer(bufferFull.getBuffer()); 
        frameBufferController.setBackBufferReady(true);
    }

    watchdog.adjustCycleTime();

}