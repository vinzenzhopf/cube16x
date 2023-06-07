// /*
//  * FireworksAnimation.h
//  *
//  * Created: 07.11.2021
//  * Author: Vinzenz hopf (happyfreak.de)
//  */ 

// #include "FireworksAnimation.h"

// FireworksAbstractProjectile::FireworksAbstractProjectile(){
// }
// bool FireworksAbstractProjectile::isAlive(){
//     return alive;
// }

// FireworksProjectile::FireworksProjectile(){

// }
// bool FireworksProjectile::initialize(ExecuteState executeState, glm::vec3 pos, glm::vec3 v, glm::vec3 a, int ttl) {
//     return true;
// }
// bool FireworksProjectile::update(ExecuteState executeState, uint32_t const currentTicks) {
//     return true;
// }
// bool FireworksProjectile::draw(ExecuteState executeState, FrameBuffer *buffer, uint32_t const currentTicks) {
//     return true;
// }

// FireworksCharge::FireworksCharge(){
// }
// bool FireworksCharge::initialize(ExecuteState executeState, glm::vec3 pos, glm::vec3 v, glm::vec3 a, int ttl) {
//     return true;
// }   
// bool FireworksCharge::update(ExecuteState executeState, uint32_t const currentTicks) {
//     return true;
// }
// bool FireworksCharge::draw(ExecuteState executeState, FrameBuffer *buffer, uint32_t const currentTicks) {
//     return true;
// }


// FireworksAnimation::FireworksAnimation() :
//                     FrameGenerator(10000),
//                     G(0.0, 0.0, 9.81),
//                     cycleCount(0),
//                     planeIndex(0) {
    
// }

// void FireworksAnimation::initializeFrameSequence(uint32_t currentTicks) {
//     FrameGenerator::initializeFrameSequence(currentTicks);
//     planeIndex = 0;
//     tmpBuffer.clearBuffer();
// }

// void FireworksAnimation::startFrame(buffer_t *nextFrame, uint32_t const currentTicks) {
//     FrameGenerator::startFrame(nextFrame, currentTicks);
//     cycleCount = 0;
// }

// void FireworksAnimation::generateCyclicBase(uint32_t const currentTicks) {
//     FrameGenerator::generateCyclicBase(currentTicks);
//     switch(cycleCount){
//         case 0:
//             tmpBuffer.clearBuffer();
//             break;
//         case 1: 
//             tmpBuffer.setPlane(ECubeDirection::Z, planeIndex, 1);
//             break;
//         case 2:  
//             tmpBuffer.copyToBuffer(frame);
//             setFrameFinished();
//             break;
//     }
//     cycleCount++;
// }

// void FireworksAnimation::endFrame(uint32_t const currentTicks) {
//     FrameGenerator::endFrame(currentTicks);
//     planeIndex++;
//     if(planeIndex >= CUBE_EDGE_SIZE){
//         setSequenceFinished();
//     }
// }
