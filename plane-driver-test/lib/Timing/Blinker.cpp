#include "Blinker.h"

#include <core_pins.h>

#include "UpdateLimiter.h"

void Blinker::run_and_wait() {
	UpdateLimiter limiter(_period);
	uint32_t open_toggles(2 * _times);
	while (open_toggles) {
		if (limiter) {
			digitalWriteFast(_pin, !digitalReadFast(_pin));
			--open_toggles;
		}
	}
}
