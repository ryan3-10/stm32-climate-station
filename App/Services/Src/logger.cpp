#include "logger.h"
#include "math.h"
#include "time.h"

void Logger::log() {
	// TODO implement logging logic
	lastLogTime = getTick();
}

bool Logger::needsToLog() const {
	if (!logConfig.enabled) {
		return false;
	}

	auto miliInterval = hoursToMili(logConfig.hourInt) + minToMili(logConfig.minInt);
	return getTick() - lastLogTime >= miliInterval;
}

void Logger::onSettingsChange(const Settings& settings) {
	logConfig = settings.log;
}



