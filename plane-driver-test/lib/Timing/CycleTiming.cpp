#include "CycleTiming.h"


elapsedCycles::elapsedCycles() {
	Timing::enable_hw_cycle_counter();
	_cyclecount = ARM_DWT_CYCCNT;
}

elapsedCycles::elapsedCycles(Timing::duration_t val) {
	Timing::enable_hw_cycle_counter();
	_cyclecount = ARM_DWT_CYCCNT - val;
}

elapsedCycles::elapsedCycles(const elapsedCycles& rhs) {
	ARM_DWT_CTRL |= 1;
	_cyclecount = rhs._cyclecount;
}

elapsedCycles::operator Timing::duration_t() const {
	return ARM_DWT_CYCCNT - _cyclecount;
}

elapsedCycles& elapsedCycles::operator=(const elapsedCycles& rhs) {
	_cyclecount = rhs._cyclecount;
	return *this;
}

elapsedCycles& elapsedCycles::operator=(Timing::duration_t val) {
	_cyclecount = ARM_DWT_CYCCNT - val;
	return *this;
}

elapsedCycles& elapsedCycles::operator-=(Timing::duration_t val) {
	_cyclecount += val;
	return *this;
}

elapsedCycles& elapsedCycles::operator+=(Timing::duration_t val) {
	_cyclecount -= val;
	return *this;
}

elapsedCycles elapsedCycles::operator-(Timing::duration_t val) const {
	elapsedCycles r(*this);
	r._cyclecount += val;
	return r;
}

elapsedCycles elapsedCycles::operator+(Timing::duration_t val) const {
	elapsedCycles r(*this);
	r._cyclecount -= val;
	return r;
}

namespace Timing {

	void reset_hw_cycle_counter(time_point_t reset_value) {
		// Write value to cycle count register
		ARM_DWT_CYCCNT = reset_value;
	}

	void enable_hw_cycle_counter() {
		// Write "enable debug and monitoring" into debug exeption and monitor control register
		ARM_DEMCR |= ARM_DEMCR_TRCENA;
		// Wirte "enable cycle count" into DWT controll register
		ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
	}

}

void HardwareCycleClock::enable() {
	Timing::enable_hw_cycle_counter();
}

void HardwareCycleClock::reset(rep reset_value) {
	Timing::reset_hw_cycle_counter(reset_value);
}
