
#include "CubeCore.h"

#include "BoardConfig.h"
#include "Base/ModuleManager.h"
#include "Watchdog.h"
#include "FrameBuffer.h"
#include "FrameBufferController.h"
#include "Drawing/PlaneDataOutputWriter.h"
#include "Drawing/PlaneOutputWriter.h"
#include "Drawing/DrawController.h"

#include "PlaylistManager.h"
#include "AnimationController.h"

#include "Animation/FullOnAnimation.h"
#include "Animation/TestAnimation.h"
#include "Animation/PlaneWalkerAnimation.h"
#include "Animation/LedWalkerAnimation.h"
#include "Animation/RandomToggleAnimation.h"
#include "Animation/RandomOnOffAnimation.h"
#include "Animation/RaindropsAnimation.h"
#include "Animation/FallingLedsAnimation.h"

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

PlaylistManager playlistManager;
AnimationController animationController(
    &frameBufferController,
    &playlistManager,
    ANIMATION_FRAME_TIME_US
);

FullOnAnimation fullOnAnimation;
TestAnimation testAnimation;
PlaneWalkerAnimation planeWalkerAnimation;
LedWalkerAnimation ledWalkerAnimation;
RandomToggleAnimation randomToggleAnimation;
RandomOnOffAnimation randomOnOffAnimation;
RaindropsAnimation raindropsAnimation;
FallingLedsAnimation fallingLedsAnimation;

enum class EAnimationType{
    eFullOn,
    eFullOff,
    eLedsAlternating,
    eWalkingLed,
    eBlink,
    ePlaneWalker,
    eColumnWalker,
    eIterateLeds,
    eRainDrops
};

FrameBuffer bufferFull;

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
    moduleManager.registerModule(&animationController);

    // playlistManager.addAnimation(&fullOnAnimation);
    // playlistManager.addAnimation(&testAnimation);
    
    playlistManager.addAnimation(&raindropsAnimation);
    playlistManager.addAnimation(&planeWalkerAnimation);
    // playlistManager.addAnimation(&randomToggleAnimation);
    // playlistManager.addAnimation(&ledWalkerAnimation);
    // playlistManager.addAnimation(&randomOnOffAnimation);
    // playlistManager.addAnimation(&fallingLedsAnimation);


    bufferFull.setBuffer();
}

void loop() {

    watchdog.initCycle();

    moduleManager.cyclic();
    // if(moduleManager.isInitialized() && frameBufferController.isFrontBufferReady()){
    //     // i++;
    //     // if(i > 200){
    //     //     if(bAlternating){
    //     //         frameBufferController.copyBuffer(bufferEmpty.getBuffer());  
    //     //     }else{
    //     //         frameBufferController.copyBuffer(bufferFull.getBuffer());  
    //     //     }
    //     //     bAlternating = !bAlternating;
    //     //     i = 0;
    //     // }
    //     bufferFull.copyToBuffer(frameBufferController.getBackBuffer()); 
    //     frameBufferController.setBackBufferReady();
    // }

    watchdog.adjustCycleTime();

}