#include "CubeDataInterpreter.h"

#include "../../MainControllerAVR/MainController/lib/CubeIO.h"
#include <sstream>
#include <bitset>


CubeDataInterpreter::CubeDataInterpreter()
	: _shift_registers{}
	, _current_register(0) {
}

std::string CubeDataInterpreter::to_string() const {
	std::ostringstream out;

	for (int i = 0; i < _shift_registers.size() / 2; i+=2) {
		std::bitset<16> row(0UL);
		for (int pos = 0; pos < 8; ++pos) {
			int mask = 1 << pos;
			row.set(i, (_shift_registers[i] & mask));
			row.set(i+8, (_shift_registers[i+1] & mask));
		}
		out << row << '\n';
	}

	return out.str();
}

void CubeDataInterpreter::reset() {
	_shift_registers.assign(0);
}

void CubeDataInterpreter::InitIOPorts() {
};
void CubeDataInterpreter::OutputEnable() {
};
void CubeDataInterpreter::OutputDisable() {
};
void CubeDataInterpreter::TriggerColumnClock() {
	_shift_registers[_current_register] = *const_cast<uint8_t*>(PORT_COLUMN);
	++_current_register;
	_current_register %= _shift_registers.size();
};
void CubeDataInterpreter::TriggerPlaneClock() {
};
void CubeDataInterpreter::TriggerColumnSto()	{
};
void CubeDataInterpreter::TriggerPlaneSto() {
};
void CubeDataInterpreter::TriggerSto() {
};
void CubeDataInterpreter::InitDataDirections() {
};