#include "clock.h"
#include "logger.h"
#include "math.h"
#include "utils.h"

bool Logger::needsToLog() const {
	if (!logConfig.enabled) {
		return false;
	}

	auto miliInterval = Utils::hoursToMili(logConfig.hourInt) + Utils::minToMili(logConfig.minInt);
	return Utils::getTick() - lastLogTime >= miliInterval;
}

void Logger::onSettingsChange(const Settings& settings) {
	if (settings.log != logConfig) {
		logConfig = settings.log;
		if (logConfig.enabled) {
//			log();
		}
	}
}
