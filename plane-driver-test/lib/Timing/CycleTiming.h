#pragma once

#include <inttypes.h>
#include <chrono>
#include <kinetis.h>

#include "Timing.h"


namespace Timing {

	// Typedef to emphasise the meaning of corresponding variables
	using time_point_t = timing_t;
	// Typedef to emphasise the meaning of corresponding variables
	using duration_t = timing_t;

	void enable_hw_cycle_counter();
	void reset_hw_cycle_counter(time_point_t reset_value = 0U);

	inline time_point_t cycles() {
		return ARM_DWT_CYCCNT;
	}
	
	// Convert nano-seconds to cpu-cylces
	constexpr duration_t ns_to_cycles(duration_t ns) {
		// 1 ns = 1sec / 1'000'000'000
		// 1 cycle = 1sec / F_CPU
		// Hence ideally cycles = ns * F_CPU / 1'000'000'000 but a 32-bit int could overflow during the multiplication.
		// The conversion factor F_CPU / 1'000'000'000 is zero due to integer division.
		// Using an optimized conversion for a fixed F_CPU seems reasonable.
		static_assert(F_CPU == 180000000, "F_CPU missmatch");
		// For F_CPU = 180MHz the exact ratio is 9/50
		// ns_max before overflow is (2^32 / 9) which is a bit more than 470ms
		// ns_res is a little less than 6ns 
		return ns * 9U / 50U;
	}

	// Convert cpu-cylces to nano-seconds
	constexpr duration_t cycles_to_ns(duration_t cycles) {
		// 1 ns = 1sec / 1'000'000'000
		// 1 cycle = 1sec / F_CPU
		// Hence ideally ns = cycles * 1'000'000'000 / F_CPU but a 32-bit int could overflow during the multiplication.
		// The conversion factor 1'000'000'000 / F_CPU is reasonably small constant but would lead to a crude result (integer division).
		// Using an optimized conversion for a fixed F_CPU seems reasonable.
		static_assert(F_CPU == 180000000, "F_CPU missmatch");
		// For F_CPU = 180MHz the exact ratio is 50/9
		// cycles_max before overflow is (2^32 / 50) which is a bit more than 85 million cycles (or 470ms)
		return cycles * 50U / 9U;
	}

	// Convert micro-seconds to cpu-cylces
	constexpr duration_t us_to_cycles(duration_t us) {
		// 1 us = 1sec / 1'000'000
		// 1 cycle = 1sec / F_CPU
		// Hence ideally cycles = us * F_CPU / 1'000'000 but a 32-bit int could overflow during the multiplication.
		// The conversion factor F_CPU / 1'000'000 is reasonably small, but using an optimized conversion for a fixed F_CPU still seems reasonable.
		static_assert(F_CPU == 180000000, "F_CPU missmatch");
		// For F_CPU = 180MHz the exact ratio is 180/1
		// us_max before overflow is (2^32 / 180) which is a bit more than 23 million cycles (or 132ms)
		return us * 180U;
	}

	// Convert cpu-cylces to micro-seconds
	constexpr duration_t cycles_to_us(duration_t cycles) {
		// 1 us = 1sec / 1'000'000
		// 1 cycle = 1sec / F_CPU
		// Hence ideally ns = cycles * 1'000'000 / F_CPU but a 32-bit int could overflow during the multiplication.
		// The conversion factor 1'000'000 / F_CPU is zero due to integer division.
		// Using an optimized conversion for a fixed F_CPU seems reasonable.
		static_assert(F_CPU == 180000000, "F_CPU missmatch");
		// For F_CPU = 180MHz the exact ratio is 1/180
		return cycles / 180U;
	}

	namespace Pimpl {
		constexpr auto one_million(1000000U);
		constexpr auto one_billion(1000000000U);

		static_assert(cycles_to_ns(F_CPU / 4) == one_billion / 4, "Conversion-Error: Cycles => ");
		static_assert(cycles_to_us(F_CPU / 4) == one_million / 4, "Conversion-Error: Cycles => micro-seconds");

		static_assert(ns_to_cycles(one_billion / 4) == F_CPU / 4, "Conversion-Error: nano-seconds => Cycles");
		static_assert(us_to_cycles(one_million / 4) == F_CPU / 4, "Conversion-Error: micro-seconds => Cycles");
	}

}


class elapsedCycles {
public:
	elapsedCycles();
	explicit elapsedCycles(Timing::duration_t val);
	elapsedCycles(const elapsedCycles &orig);
	explicit operator Timing::duration_t() const;
	elapsedCycles& operator=(const elapsedCycles &rhs);
	elapsedCycles& operator=(Timing::duration_t val);
	elapsedCycles& operator-=(Timing::duration_t val);
	elapsedCycles& operator+=(Timing::duration_t val);
	elapsedCycles operator-(Timing::duration_t val) const;
	elapsedCycles operator+(Timing::duration_t val) const;

private:
	Timing::duration_t _cyclecount;
};

// std::chrono clock using the ARM-M4 cycle-counter as a backend
// WIP - Please use Timing:: for now, since using the time_points and duration objects with mixed cv-qualifiers isn't possible
class HardwareCycleClock {
public:
	using rep = Timing::timing_t;
	using period = std::ratio<1, F_CPU>;
	using duration = std::chrono::duration<rep, period>;
	using time_point = std::chrono::time_point<HardwareCycleClock>;
	static const bool is_steady = false;

	static inline time_point now() {
		return time_point(duration(Timing::cycles()));
	}

	static void enable();
	static void reset(rep reset_value = 0U);

};



