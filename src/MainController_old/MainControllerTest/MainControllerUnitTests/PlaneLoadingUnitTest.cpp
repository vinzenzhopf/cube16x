#include <SDKDDKVer.h>
#include "CppUnitTest.h"
#include <inttypes.h>
#include "../../MainControllerSharedResources/MockupFunctions.h"

#include "../../MainControllerAVR/MainController/lib/CubeIO.h"
#include "../../MainControllerAVR/MainController/lib/CubeFrameBuffer.h"
#include "../../MainControllerAVR/MainController/lib/CubeLogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class PlaneLoadingUnitTest;

PlaneLoadingUnitTest* singleton;

TEST_CLASS(PlaneLoadingUnitTest)
{
public:
	PlaneLoadingUnitTest() {
		singleton = this;
	};

	/*TEST_METHOD(test_triggering) {
		trigger_cnt = 0;
		Cube_InitDataBuffer();
		Cube_WritePlane(0);
		Assert::AreEqual(trigger_cnt, 1U, L"Dis fucked up");
	}*/


	uint32_t trigger_cnt;
};

