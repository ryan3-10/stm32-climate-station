#include "ds3231_clock.h"
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
	char dtBuf[25];
	DateTime dt;

	if (clock.currentDateTime(dt) == CLOCK_STATUS::OK) {
		snprintf(
			dtBuf,
			sizeof(dtBuf),
			"%02u/%02u/%02u %02u:%02u:%02u",
			dt.month, dt.date, dt.year, dt.hour, dt.minute, dt.second
		);
	} else {
		strncpy(dtBuf, "Clock Error", sizeof(dtBuf) - 1);
	}

	char weatherBuf[30] = {0};
	if (cachedReading.statusOk) {
		snprintf(
			weatherBuf,
			sizeof(weatherBuf),
			"%.1fF %.1f%%",
			cachedReading.data.temp, cachedReading.data.hum
		);
	} else {
		strncpy(weatherBuf, "Sensor Error", sizeof(weatherBuf) - 1);
	}

	char masterBuf[60];
	snprintf(masterBuf, sizeof(masterBuf), "%s %s\n", dtBuf, weatherBuf);

	fileManager.writeToFile("log.txt", masterBuf);
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
