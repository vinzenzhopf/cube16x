
#pragma once

#include <unity.h>
#include "IPlaylistManager.h"
#include "PlaylistManager.h"
#include "Animation/FrameGenerator.h"
#include "Animation/ICyclicFrameGeneration.h"

#include <iostream>

using namespace std;

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

// void test_function_calculator_addition(void) {
//     TEST_ASSERT_EQUAL(32, calc.add(25, 7));
// }

class AnimationMock : public ICyclicFrameGeneration {
    protected:
        const int index;
    public:
        AnimationMock(const int index) :
            index(index) {
        }
        virtual ~AnimationMock() = default;

        void initializeFrameSequence(uint32_t currentTicks) override{
            std::cout << index << "::initializeFrameSequence(currentTicks=" << currentTicks << ")" << std::endl;
        }
        void startFrame(buffer_t *nextFrame, uint32_t currentTicks, uint32_t totalFrameTimeUs) override{
            std::cout << index << "::startFrame(nextFrame=" << nextFrame << ", currentTicks=" << currentTicks << ", totalFrameTimeUs=" << totalFrameTimeUs << ")" << std::endl;
        }
        void generateCyclicBase(uint32_t currentTicks) override{
            std::cout << index << "::generateCyclicBase(currentTicks=" << currentTicks << ")" << std::endl;
        }
        void endFrame() override{
            std::cout << index << "::endFrame()" << std::endl;
        }

        bool isSequenceFinished() override{
            return false;
        }
        // bool isFrameFinished() override{
        //     return false;
        // }
        uint32_t getFrameCounter() override{
            return 0;
        }

        uint32_t getAnimationFrameTimeUs() override{
            return 20*1000;
        }
        bool getRepeatUntilTimeExceeded() override{
            return false;
        }
};

void PlaylistManagerTest_get_current_animation(){
    PlaylistManager playlistManager;
    FrameGenerator animation(2000, true);

    IPlaylistManager* manager = &playlistManager;
    ICyclicFrameGeneration *p = nullptr;

    manager->addAnimation(&animation);

    TEST_ASSERT_EQUAL(1, manager->getEntryCount());
    TEST_ASSERT_EQUAL(0, manager->getCurrentIndex());

    p = manager->getCurrentAnimation();
    TEST_ASSERT_NOT_NULL(p);

    buffer_t t;
    p->startFrame(&t, 42, 3);
    p->generateCyclicBase(42);
    p->endFrame();

    TEST_ASSERT_EQUAL_PTR_MESSAGE(p, &animation, "Address does not match");
}

void PlaylistManagerTest_get_next_entry(void) {
    PlaylistManager playlistManager;
    AnimationMock animation1(0);
    AnimationMock animation2(1);
    AnimationMock animation3(2);

    IPlaylistManager* manager = &playlistManager;

    manager->addAnimation(&animation1);
    manager->addAnimation(&animation2);
    manager->addAnimation(&animation3);

    TEST_ASSERT_EQUAL(3, manager->getEntryCount());
    TEST_ASSERT_EQUAL(0, manager->getCurrentIndex());

    ICyclicFrameGeneration *p = nullptr;
    buffer_t t;
    uint32_t currentTicks;
    ICyclicFrameGeneration *selectedAnimations[15];
    for(int i = 0; i < 15; i++){
        p = manager->getNextAnimation();
        selectedAnimations[i] = p;
        TEST_ASSERT_NOT_NULL(p);
        
        currentTicks = rand();
        p->initializeFrameSequence(currentTicks);
        p->startFrame(&t, currentTicks, i);
        p->generateCyclicBase(currentTicks);
        p->endFrame();
    }
    bool onlyOneAnimation = true;
    p = selectedAnimations[0];
    std::cout << "0 " << p << endl;
    for(int i = 1; i < 15; i++){
        p = selectedAnimations[i];
        std::cout << i << " " << p << endl;
        if(selectedAnimations[0] != selectedAnimations[i]){
            onlyOneAnimation = false;
        }
    }
    TEST_ASSERT_FALSE_MESSAGE(onlyOneAnimation, "NextAnimation returns only one animations.")
}
