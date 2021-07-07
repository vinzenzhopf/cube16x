#include <SDKDDKVer.h>
#include "CppUnitTest.h"
#include <inttypes.h>

#include "CubeFrame.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestCubeFrameUnitTest)
{
public:
	TestCubeFrameUnitTest() {
		srand(time(NULL));
	};

	TEST_METHOD(TestTestCubeFrame) {
		std::bitset
		

		CubeFrame frame;
		//frame.



		//trigger_cnt = 0;
		//Assert::AreEqual(trigger_cnt, 1U, L"Dis fucked up");

	}
};