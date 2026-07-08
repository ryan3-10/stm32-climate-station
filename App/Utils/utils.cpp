#include "utils.h"
#include <stdio.h>

Utils::LoggableString Utils::getLoggableString(const DateTime::Model& dt) {
	LoggableString result{};
	snprintf(
		result.data(),
		result.size(),
		"%02u/%02u/%02u %02u:%02u:%02u",
		dt.month, dt.date, dt.year, dt.hour, dt.minute, dt.second
	);
	return result;
}

Utils::LoggableString Utils::getLoggableString(const WeatherData& wd) {
	LoggableString result{};
	snprintf(
		result.data(),
		result.size(),
		"%.1fF %.1f%%",
		wd.temp, wd.hum
	);
	return result;
}


