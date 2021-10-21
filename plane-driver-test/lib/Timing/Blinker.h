#pragma once

#include <inttypes.h>

class Blinker {
public:
	constexpr Blinker(uint8_t pin, uint32_t times = 1, uint32_t period_ms = 500)
		: _pin(pin)
		, _times(times)
		, _period(period_ms) {
	};
	~Blinker() = default;

	void run_and_wait();

private:
	uint8_t _pin;
	uint32_t _times;
	uint32_t _period;
};