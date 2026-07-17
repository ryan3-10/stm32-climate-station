#ifndef HARDWARE_INC_TIME_UTIL_H_
#define HARDWARE_INC_TIME_UTIL_H_

#include "clock.h"
#include "weather_models.h"
#include <array>
#include <stdint.h>

namespace Utils {
	using LoggableString = std::array<char, 30>;

	inline uint32_t hoursToMili(uint32_t hours) { return hours * 60 * 60 * 1000; }
	inline uint32_t minToMili(uint32_t minutes) { return minutes * 60 * 1000; }
	LoggableString getLoggableString(const DateTime::Model& dt);
	LoggableString getLoggableString(const WeatherData& dt);
}

#endif /* HARDWARE_INC_TIME_H_ */
