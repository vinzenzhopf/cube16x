//#include <Arduino.h>



// void setup() {
//   // put your setup code here, to run once:
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

#include <avr/io.h>

#include "BoardConfig.h"
#include "Base/ModuleManager.h"
#include "FrameBuffer.h"
#include "FrameBufferController.h"
#include "Drawing/PlaneDataOutputWriter.h"
#include "Drawing/PlaneOutputWriter.h"
#include "Drawing/DrawController.h"

void SetBuffer_LedAlternating(buffer_t * pBuffer){
    for(uint8_t i = 0; i < 16; i++){
        for(uint8_t j = 0; j < 16; j++){
            pBuffer->asPlanes[i].asShort[j] = (j%2==0)?0b1010101010101010:0b0101010101010101;
        }
    }
}

int main(void)
{
    ModuleManager moduleManager;
    FrameBufferController frameBufferController;
    PlaneOutputWriter planeOutputWriter(
        &(PORT_CONTROL_OUT),
        PLANE_CLK, 
        PLANE_OE,
        PLANE_STO,
        PLANE_DATA,
        2
    );
    PlaneDataOutputWriter planeDataOutputWriter(
        &(PORT_COLUMN), 
        &(PORT_CONTROL_OUT), 
        COL_CLK, 
        COL_OE,
        COL_STO,
        2
    );
    DrawController drawController(
        &planeOutputWriter, 
        &planeDataOutputWriter,
        &frameBufferController, 
        10
    );

    Device_InitIOPorts();
    Device_InitDataDirections();

    moduleManager.registerModule(&frameBufferController);
    moduleManager.registerModule(&planeOutputWriter);
    moduleManager.registerModule(&planeDataOutputWriter);
    moduleManager.registerModule(&drawController);

    //manually pull OE to High (FOR TESTING)
    PORT_CONTROL_OUT |= (1<<PLANE_OE | 1<<COL_OE);

    while (1) 
    {
        moduleManager.cyclic();

        if(moduleManager.isInitialized()){
            SetBuffer_LedAlternating(frameBufferController.getBackBuffer());
            frameBufferController.setBackBufferReady(true);
        }
    }
}
