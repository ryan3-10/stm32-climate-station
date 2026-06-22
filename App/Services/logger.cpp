#include "logger.h"
#include "math.h"
#include "time_service.h"
#include <stdio.h>
#include <string.h>

void Logger::init() {
	fileManager.init();
	fileManager.createFileIfNotExist("log.txt");
}

void Logger::log() {
	char buff[30] = {0};

	if (cachedWeather.statusOk) {
		snprintf(
			buff,
			sizeof(buff),
			"%.1fF %.1f%%\n",
			cachedWeather.temp, cachedWeather.hum
		);
	} else {
		strncpy(buff, "Sensor Error\n", sizeof(buff) - 1);
	}

	fileManager.writeToFile("log.txt", buff);
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
	if (settings.log != logConfig) {
		logConfig = settings.log;
		if (logConfig.enabled) {
			log();
		}
	}
}
