#pragma once

#include "MockupWrapper.h"
#include <array>
#include <string>
#include <bitset>

 class CubeDataInterpreter : public MockupWrapper {
 public:
	 CubeDataInterpreter();

	void InitIOPorts() override;
	void OutputEnable() override;
	void OutputDisable() override;
	void TriggerColumnClock() override;
	void TriggerPlaneClock() override;
	void TriggerColumnSto() override;
	void TriggerPlaneSto() override;
	void TriggerSto() override;
	void InitDataDirections() override;

	void reset();

	std::string to_string() const;
 
 private:
	 size_t _current_register;
	 std::bitset<4096> _frame_data;
	 std::array<uint8_t, 32> _shift_registers;
 };