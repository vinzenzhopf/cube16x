#include <avr/io.h>

#include "BoardConfig.h"
#include "Base/ModuleManager.h"
#include "Watchdog.h"
#include "FrameBuffer.h"
#include "FrameBufferController.h"
#include "Drawing/PlaneDataOutputWriter.h"
#include "Drawing/PlaneOutputWriter.h"
#include "Drawing/DrawController.h"

int main(void)
{
    Device_InitIOPorts();
    Device_InitDataDirections();
    //Set ErrorLED to HIGH during initializaton
    PORT_INFO |= (1<<PIN_INFO_ERR_LED);

    ModuleManager moduleManager;
    Watchdog watchdog(
        &(PORT_INFO),
        PIN_INFO_CYCL_LED,          //INFO_CYCLE_PIN
        PIN_INFO_ERR_LED,           //INFO_SYSOK_PIN
        &(PORT_PLANE_CONTROL),      //PORT_PLANE_CTL
        PIN_PLANE_OE,               //PLANE_OE_PIN
        &(PORT_COL_CONTROL),        //PORT_DATA_CTL
        PIN_COL_OE                  //DATA_OE_PIN
    );
    FrameBufferController frameBufferController;
    PlaneOutputWriter planeOutputWriter(
        &(PORT_CONTROL_OUT),
        PIN_PLANE_CLK, 
        PIN_PLANE_STO,
        PIN_PLANE_DATA,
        0
    );
    PlaneDataOutputWriter planeDataOutputWriter(
        &(PORT_COLUMN), 
        &(PORT_CONTROL_OUT), 
        PIN_COL_CLK, 
        PIN_COL_STO,
        0
    );
    DrawController drawController(
        &planeOutputWriter, 
        &planeDataOutputWriter,
        &frameBufferController,
        &watchdog,
        10
    );

    moduleManager.registerModule(&watchdog);
    moduleManager.registerModule(&frameBufferController);
    moduleManager.registerModule(&planeOutputWriter);
    moduleManager.registerModule(&planeDataOutputWriter);
    moduleManager.registerModule(&drawController);

    FrameBuffer bufferAlternating, bufferFull, bufferEmpty;
    bufferAlternating.setBufferAlternating();
    bufferFull.setBuffer();
    bufferEmpty.clearBuffer();

    while (1) 
    {
        moduleManager.cyclic();

        if(moduleManager.isInitialized() && frameBufferController.isFrontBufferReady()){
            frameBufferController.copyBuffer(bufferFull.getBuffer());  
            frameBufferController.setBackBufferReady(true);
        }
    }
}
