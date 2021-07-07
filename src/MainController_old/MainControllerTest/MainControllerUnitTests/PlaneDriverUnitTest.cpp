#include <SDKDDKVer.h>
#include "CppUnitTest.h"
#include <inttypes.h>
#include "../../MainControllerSharedResources/MockupFunctions.h"

#include "../../MainControllerAVR/MainController/lib/CubeIO.h"
#include "../../MainControllerAVR/MainController/lib/CubeFrameBuffer.h"
#include "../../MainControllerAVR/MainController/lib/CubeLogic.h"

#include "MockupWrapper.h"

#include <sstream>
#include <array>
#include <vector>

#include <iostream>
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

enum STORAGE_INDEX {
	IO_PORT, OUTPUT_ENABLE, OUTPUT_DISABLE, COLUMN_CLOCK, PLANE_CLOCK, COLUMN_STORE, PLANE_STORE, TRIGGER_STORE, DATA_DIRECTIONS, LENGTH
};

TEST_CLASS(PlaneDriverUnitTest), public MockupWrapper{
public:
	PlaneDriverUnitTest() 
		: _action_count{} {
		set_target(this);
		Cube_InitDataBuffer();
		//_output_capture.reserve(16 * 1024);
	};

	TEST_METHOD(TestColumnClockCount) {
		reset();
		Cube_WritePlane(0);
		std::wostringstream out;
		constexpr auto expected_val(32U);
		const auto& real_val(_action_count[STORAGE_INDEX::COLUMN_CLOCK]);
		out << "Expected: " << expected_val << " - Real: " << real_val;
		Assert::AreEqual(real_val, expected_val, out.str().c_str(), LINE_INFO());
	}

	TEST_METHOD(TestPlaneClockCount) {
		reset();
		Cube_WritePlane(0);
		std::wostringstream out;
		constexpr auto expected_val(1U);
		const auto& real_val(_action_count[STORAGE_INDEX::PLANE_CLOCK]);
		out << "Expected: " << expected_val << " - Real: " << real_val;
		Assert::AreEqual(real_val, expected_val, out.str().c_str(), LINE_INFO());
	}

	/*TEST_METHOD(TestPlaneClockCount) {
		reset();
		Cube_WritePlane(0);
		std::wostringstream out;
		constexpr auto expected_val(1U);
		const auto& real_val(_action_count[STORAGE_INDEX::PLANE_CLOCK]);
		out << "Expected: " << expected_val << " - Real: " << real_val;
		Assert::AreEqual(real_val, expected_val, out.str().c_str(), LINE_INFO());
	}*/

	//TEST_METHOD(TestDataWritten) {
	//	reset();
	//	outputBuffer->asPlanes[0].asBytes[0] = 127U;
	//	Cube_WritePlane(0);
	//	std::wostringstream out;
	//	constexpr auto expected_val(33U);
	//	const auto real_val(_output_capture.size());
	//	out << "Expected: " << expected_val << " - Real: " << real_val;
	//	out << '\n';
	//	for (const auto b : _output_capture) {
	//		out << std::bitset<8>(b) << '\n';
	//	}
	//	Assert::AreEqual(real_val, expected_val, out.str().c_str(), LINE_INFO());
	//}



	void InitIOPorts() override {
		++_action_count[STORAGE_INDEX::IO_PORT];
	};
	void OutputEnable() override {
		++_action_count[STORAGE_INDEX::OUTPUT_ENABLE];
	};
	void OutputDisable() override {
		++_action_count[STORAGE_INDEX::OUTPUT_DISABLE];
	};
	void TriggerColumnClock() override {
		++_action_count[STORAGE_INDEX::COLUMN_CLOCK];
		//_output_capture.push_back(*const_cast<uint8_t*>(PORT_COLUMN));
	};
	void TriggerPlaneClock() override {
		++_action_count[STORAGE_INDEX::PLANE_CLOCK];
	};
	void TriggerColumnSto()	override {
		++_action_count[STORAGE_INDEX::COLUMN_STORE];
	};
	void TriggerPlaneSto() override {
		++_action_count[STORAGE_INDEX::PLANE_STORE];
	};
	void TriggerSto() override {
		++_action_count[STORAGE_INDEX::TRIGGER_STORE];
	};
	void InitDataDirections() override {
		++_action_count[STORAGE_INDEX::DATA_DIRECTIONS];
	};

private:
	void reset() {
		_action_count.fill(0);
		//_output_capture.clear();
	}

	std::array<uint32_t, STORAGE_INDEX::LENGTH> _action_count;
	//std::vector<uint8_t> _output_capture;

};


