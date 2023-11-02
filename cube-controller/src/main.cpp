
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

#include "Animations/FullOnAnimation.h"
#include "Animations/TestAnimation.h"
#include "Animations/PlaneWalkerAnimation.h"
#include "Animations/LedWalkerAnimation.h"
#include "Animations/RandomToggleAnimation.h"
#include "Animations/RandomOnOffAnimation.h"
#include "Animations/RaindropsAnimation.h"
#include "Animations/FallingLedsAnimation.h"
#include "Animations/BouncingCubeAnimation.h"
#include "Animations/PlaneWalkerAnimation2.h"
#include "Animations/NetworkStream/NetworkStreamAnimation.h"

#include "NetworkStreaming.h"

#include "Entropy.h"

#include <EEPROM.h>

Watchdog watchdog(
    PIN_INFO_CYCL_LED,          //INFO_CYCLE_PIN
    PIN_INFO_PWR_SIG,           //INFO_SYSOK_PIN
    PIN_INFO_ERR_LED,           //INFO_SYSERR_PIN
    PIN_INFO_DBG_LED,           //INFO_DBG_PIN
    PIN_OE,                     //PLANE_OE_PIN
    CYCLE_TIME_US               //TARGET_CYCLE_TIME_US
);
ModuleManager moduleManager(
    &watchdog
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
FrameStatistics frameStatistics;
AnimationController animationController(
    &frameBufferController,
    &playlistManager,
    &frameStatistics,
    ANIMATION_FRAME_TIME_US
);

FullOnAnimation fullOnAnimation;
TestAnimation testAnimation;
PlaneWalkerAnimation planeWalkerAnimation;
PlaneWalkerAnimation2 planeWalkerAnimation2;
LedWalkerAnimation ledWalkerAnimation;
RandomToggleAnimation randomToggleAnimation;
RandomOnOffAnimation randomOnOffAnimation;
RaindropsAnimation raindropsAnimation;
FallingLedsAnimation fallingLedsAnimation;
BouncingCubeAnimation bouncingCubeAnimation;
NetworkStreamAnimation networkStreamAnimation(
    30000 //networkTimeoutMs
);

NetworkStreaming networkStreaming(
    &networkStreamAnimation,
    MacAddress,
    DefaultIp,
    DefaultDns,
    DefaultGateway,
    DefaultSubnet,
    ServerPort
);

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

void setup() {
    BoardInitIOPorts();
    BoardInitDataDirections();

    //Set ErrorLED to HIGH during initializaton
    digitalWriteFast(PIN_INFO_ERR_LED, HIGH);

    //Serial communication to serial monitor via USB
    Serial.begin(9600); // USB is always 12 or 480 Mbit/sec
    while (!Serial) {
        ; // wait for Arduino Serial Monitor to be ready
    }
    Serial.println("Serial monitor initialized");

    moduleManager.registerModule(&watchdog);
    moduleManager.registerModule(&frameBufferController);
    moduleManager.registerModule(&planeOutputWriter);
    moduleManager.registerModule(&planeDataOutputWriter);
    moduleManager.registerModule(&drawController);
    moduleManager.registerModule(&animationController);
    moduleManager.registerModule(&frameStatistics);
    moduleManager.registerModule(&networkStreaming);

    playlistManager.addAnimation(&fullOnAnimation);
    // playlistManager.addAnimation(&testAnimation);
    
    playlistManager.addAnimation(&raindropsAnimation);
    playlistManager.addAnimation(&planeWalkerAnimation);
    // // playlistManager.addAnimation(&planeWalkerAnimation2);
    playlistManager.addAnimation(&bouncingCubeAnimation);
    // playlistManager.addAnimation(&randomToggleAnimation);
    playlistManager.addAnimation(&ledWalkerAnimation);
    // playlistManager.addAnimation(&randomOnOffAnimation);
    playlistManager.addAnimation(&fallingLedsAnimation);

    playlistManager.addPriorityAnimation(&networkStreamAnimation);

    //Call setup on all Modules
    moduleManager.setup();

    Entropy.Initialize();
}

void loop() {

    watchdog.initCycle();

    moduleManager.cyclic();

    watchdog.adjustCycleTime();
    
}
