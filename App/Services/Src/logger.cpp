#include "logger.h"
#include "math.h"

void Logger::log() {
	// TODO implement logging logic
	lastLogTime = 0;
}

bool Logger::needsToLog() const {
	if (!logConfig.enabled) {
		return false;
	}

	auto miliInterval = hoursToMili(logConfig.hourInt) + minToMili(logConfig.minInt);
	//return HAL_GetTick() - lastLogTime >= miliInterval;
	return false;
}

void Logger::onSettingsChange(const Settings& settings) {
	logConfig = settings.log;
}



