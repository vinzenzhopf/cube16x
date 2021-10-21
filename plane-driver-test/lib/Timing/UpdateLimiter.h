#pragma once

#include "elapsedMillis.h"

class UpdateLimiter {
public:
	UpdateLimiter(unsigned long period);
	~UpdateLimiter() = default;

	explicit operator bool();

private:
	elapsedMillis _elapsed_millis;
	unsigned long _period;
};