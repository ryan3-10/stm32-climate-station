#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "clock.h"
#include "config_models.h"
#include "observer.h"
#include "weather_models.h"
#include <stdio.h>
#include <utils.h>

template <typename FileWriter>
class Logger : public WeatherObserver {
public:
	Logger(const LogConfig& l, IClock& c, FileWriter& f)
		: logConfig(l)
		, clock(c)
		, fileWriter(f)
	{}

	void update();
	void setConfig(const LogConfig& l);
	void onWeatherUpdate(const SensorRead& reading) override { lastReading = reading; }


private:
	bool needsToLog() const;
	void log();

	LogConfig logConfig;
	IClock& clock;
	FileWriter& fileWriter;
	uint32_t lastLogTime = 0;
	SensorRead lastReading {};
};

#include "clock.h"
#include "logger.h"
#include "math.h"
#include "utils.h"

template <typename FileWriter>
void Logger<FileWriter>::update() {
	if (needsToLog()) {
		log();
	}
}

template <typename FileWriter>
bool Logger<FileWriter>::needsToLog() const {
	if (!logConfig.enabled) {
		return false;
	}

	auto miliInterval = Utils::hoursToMili(logConfig.hourInt) + Utils::minToMili(logConfig.minInt);
	return Utils::getTick() - lastLogTime >= miliInterval;
}

template <typename FileWriter>
void Logger<FileWriter>::log() {
	Utils::LoggableString dtStr{};
	DateTime dt;

	if (clock.now(dt)) {
		dtStr = Utils::getLoggableString(dt);
	} else {
		snprintf(dtStr.data(), dtStr.size(), "%s", "Clock Error");
	}

	Utils::LoggableString wdStr{};

	if (lastReading.statusOk) {
		wdStr = Utils::getLoggableString(lastReading.data);
	} else {
		snprintf(wdStr.data(), wdStr.size(), "%s", "Sensor Error");
	}

	char buf[60];
	snprintf(buf, sizeof(buf), "%s %s\n", dtStr.data(), wdStr.data());
	fileWriter.writeToFile("log.txt", buf);
	lastLogTime = Utils::getTick();
}

template <typename FileWriter>
void Logger<FileWriter>::setConfig(const LogConfig& l) {
	if (l != logConfig) {
		logConfig = l;

		if (logConfig.enabled) {
			log();
		}
	}
}



#endif /* SERVICES_INC_LOGGER_H_ */
