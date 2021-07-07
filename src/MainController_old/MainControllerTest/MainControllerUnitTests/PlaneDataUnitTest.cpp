#include <SDKDDKVer.h>
#include "CppUnitTest.h"
#include <inttypes.h>
#include "../../MainControllerSharedResources/MockupFunctions.h"

#include "../../MainControllerAVR/MainController/lib/CubeIO.h"
#include "../../MainControllerAVR/MainController/lib/CubeFrameBuffer.h"
#include "../../MainControllerAVR/MainController/lib/CubeLogic.h"

#include "MockupWrapper.h"

#include <string>
#include <sstream>
#include <array>
#include <vector>

#include <iostream>
#include <bitset>

#include "CubeDataInterpreter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

enum STORAGE_INDEX {
	IO_PORT, OUTPUT_ENABLE, OUTPUT_DISABLE, COLUMN_CLOCK, PLANE_CLOCK, COLUMN_STORE, PLANE_STORE, TRIGGER_STORE, DATA_DIRECTIONS, LENGTH
};

TEST_CLASS(PlaneDataUnitTest), public MockupWrapper{
public:
	PlaneDataUnitTest()
		: _data_interpreter() {
		set_target(this);
		Cube_InitDataBuffer();
	};

	TEST_METHOD(TestDataWritten) {
		reset();
		outputBuffer->asPlanes[0].asBytes[0] = 0b1111111111111111;

		Cube_WritePlane(0);

		std::wostringstream out;
		constexpr auto expected_val(42U);
		const auto real_val(42U);
		out << "Expected: " << expected_val << " - Real: " << real_val << '\n';
		out << _data_interpreter.to_string().c_str();

		Assert::AreEqual(real_val, expected_val, out.str().c_str(), LINE_INFO());
	}





	void InitIOPorts() override {
	};
	void OutputEnable() override {
	};
	void OutputDisable() override {
	};
	void TriggerColumnClock() override {
		_data_interpreter.TriggerColumnClock();
	};
	void TriggerPlaneClock() override {
	};
	void TriggerColumnSto()	override {
	};
	void TriggerPlaneSto() override {
	};
	void TriggerSto() override {
	};
	void InitDataDirections() override {
	};

private:
	void reset() {
		_data_interpreter.reset();
	}

	

	CubeDataInterpreter _data_interpreter;
};