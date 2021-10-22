/*
 * AnimationController.cpp
 *
 * Created: 11.07.2017 22:03:33
 * Author: Vinzenz Hopf (happyfreak.de)
 */ 

#include "AnimationController.h"



AnimationController::AnimationController(){
}

bool AnimationController::initialize(){
	return CyclicModule::initialize();
}

void AnimationController::cyclic(){
    CyclicModule::cyclic();

    bool bDone = false;
    switch (arrPlayListEntries[nPlayListEntry].type)
    {
    case EAnimationType::ePlaneWalker:
        break;
    
    case EAnimationType::eWalkingLed:
    default:
        break;
    }
    
    if(bDone){
        nPlayListEntry++;
        if(nPlayListEntry >= getPlayListLength()){
            nPlayListEntry = 0;
        }
    }    

}