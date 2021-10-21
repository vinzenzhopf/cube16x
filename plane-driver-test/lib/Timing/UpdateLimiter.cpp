#include "UpdateLimiter.h"

UpdateLimiter::UpdateLimiter(unsigned long period)
	: _period(period) {	
}

UpdateLimiter::operator bool() {
	if (_elapsed_millis > _period) {
		_elapsed_millis -= _period;
		return true;
	}
	return false;
}
