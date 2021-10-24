
// #pragma once

// #include <unity.h>
// #include "IPlaylistManager.h"
// #include "PlaylistManager.h"
// #include "Animation/FrameGenerator.h"
// #include "Animation/ICyclicFrameGeneration.h"

// #include <iostream>

// using namespace std;

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

// void test_function_calculator_addition(void) {
//     TEST_ASSERT_EQUAL(32, calc.add(25, 7));
// }

// class PlaylistManagerMock : public IPlaylistManager {
//     protected:        
//         ICyclicFrameGeneration *entry;
// 	public:
//         PlaylistManagerMock() {
//         }
//         virtual ~PlaylistManagerMock() = default;

//         void addAnimation(ICyclicFrameGeneration *frameGenerator) override{
//             entry = frameGenerator;
//         }
        
//         ICyclicFrameGeneration* getNextAnimation() override{
//             return entry;
//         }

//         ICyclicFrameGeneration* getCurrentAnimation() override{
//             return entry;
//         }

//         uint8_t getEntryCount() override{
//             return 1;
//         }

//         uint8_t getCurrentIndex() override{
//             return 0;
//         }
// };

// class AnimationMock : public ICyclicFrameGeneration {
//     public:
//         AnimationMock() {
//         }
//         virtual ~AnimationMock() = default;

//         void initializeFrameSequence(uint32_t currentTicks) override{
//             std::cout << "initializeFrameSequence(currentTicks=" << currentTicks << ")" << std::endl;
//         }
//         void startFrame(buffer_t *nextFrame, uint32_t currentTicks, uint32_t totalFrameTimeUs) override{
//             std::cout << "startFrame(nextFrame=" << nextFrame << ", currentTicks=" << currentTicks << ", totalFrameTimeUs=" << totalFrameTimeUs << ")" << std::endl;
//         }
//         void generateCyclicBase(uint32_t currentTicks) override{
//             std::cout << "generateCyclicBase(currentTicks=" << currentTicks << ")" << std::endl;
//         }
//         void endFrame() override{
//             std::cout << "endFrame()" << std::endl;
//         }

//         bool isSequenceFinished() override{
//             return false;
//         }
//         bool isFrameFinished() override{
//             return false;
//         }
//         uint32_t getFrameCounter() override{
//             return 0;
//         }

//         uint32_t getAnimationFrameTimeUs() override{
//             return 20*1000;
//         }
//         bool getRepeatUntilTimeExceeded() override{
//             return false;
//         }
// };

// void AnimationTest_test_playlist_manager_get_next_entry(void) {
//     PlaylistManager playlistManager;
//     AnimationMock animationMock;
//     FrameGenerator animation(2000, true);

//     IPlaylistManager* manager = &playlistManager;
//     ICyclicFrameGeneration *p = nullptr;

//     manager->addAnimation(&animationMock);

//     TEST_ASSERT_EQUAL(1, manager->getEntryCount());
//     TEST_ASSERT_EQUAL(0, manager->getCurrentIndex());

//     p = manager->getCurrentAnimation();
//     TEST_ASSERT_TRUE(true);

//     buffer_t t;
    
//     p->startFrame(&t, 42, 3);
//     p->generateCyclicBase(42);
//     p->endFrame();

//     //TEST_ASSERT_EQUAL_PTR(nullptr, p);

//     // TEST_ASSERT_NOT_NULL_MESSAGE(p, "No animation returned");
//     // TEST_ASSERT_EQUAL_PTR_MESSAGE(p, &fullOnAnimation, "Address does not match");
// }

// void AnimationTest_test_animation_controller(){
    
// }
