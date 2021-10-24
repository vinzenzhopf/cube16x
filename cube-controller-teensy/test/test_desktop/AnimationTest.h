
#include <unity.h>
#include "PlaylistManager.h"
#include "Animation/ICyclicFrameGeneration.h"
#include "Animation/FullOnAnimation.h"

#ifndef __ANIMATIONTEST_H__
#define __ANIMATIONTEST_H__


// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

// void test_function_calculator_addition(void) {
//     TEST_ASSERT_EQUAL(32, calc.add(25, 7));
// }

class PlaylistManagerMock : public IPlaylistManager {
    protected:        
        ICyclicFrameGeneration *entry;
	public:
        PlaylistManagerMock() {
        }
        virtual ~PlaylistManagerMock() = default;

        void addAnimation(ICyclicFrameGeneration *frameGenerator) override{
            entry = frameGenerator;
        }
        
        ICyclicFrameGeneration* getNextAnimation() override{
            return entry;
        }

        ICyclicFrameGeneration* getCurrentAnimation() override{
            return entry;
        }

        uint8_t getEntryCount() override{
            return 1;
        }

        uint8_t getCurrentIndex() override{
            return 0;
        }
};

void AnimationTest_test_playlist_manager_get_next_entry(void) {
    PlaylistManagerMock playlistManager;
    FullOnAnimation fullOnAnimation(2000, true);

    IPlaylistManager* manager = &playlistManager;
    ICyclicFrameGeneration *p = nullptr;


    manager->addAnimation(&fullOnAnimation);

    TEST_ASSERT_EQUAL(1, manager->getEntryCount());
    TEST_ASSERT_EQUAL(0, manager->getCurrentIndex());

    p = manager->getCurrentAnimation();
    TEST_ASSERT_TRUE(p == nullptr);
    //TEST_ASSERT_EQUAL_PTR(nullptr, p);

    // TEST_ASSERT_NOT_NULL_MESSAGE(p, "No animation returned");
    // TEST_ASSERT_EQUAL_PTR_MESSAGE(p, &fullOnAnimation, "Address does not match");
}

void AnimationTest_test_animation_controller(){
    
}

#endif //__ANIMATIONTEST_H__