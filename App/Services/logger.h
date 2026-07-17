#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "clock.h"
#include "config_models.h"
#include "hardware_utils.h"
#include "observer.h"
#include "weather_models.h"
#include "utils.h"
#include <stdio.h>

using namespace Utils;
using namespace HardwareUtils;

template <typename FileWriter>
class Logger : public Observer {
public:
	Logger(IClock& c, FileWriter& f) : clock(c), fileWriter(f) {}

	void update();
	void setConfig(const LogConfig& l);
	void onWeatherUpdate(const SensorRead& reading) override { lastReading = reading; }


private:
	static constexpr uint8_t CLK_CHECK_INT = 250;
	void log(const LoggableString& clockStamp);
	bool backupNeedToLogCheck() const;
	uint32_t minuteInt() { return (logConfig.hourInt * 3600) + (logConfig.minInt * 60); }
	IClock& clock;
	FileWriter& fileWriter;
	LogConfig logConfig{};
	SensorRead lastReading{};
	DateTime nextLogTime{};
	uint32_t lastLogTick = 0; // backup used if clock is in error state
	uint32_t lastClkCheckTick = 0; // for checking the time every CLK_CHECK_INT milis
};

template <typename FileWriter>
void Logger<FileWriter>::update() {
	if (!logConfig.enabled || timeElapsed(lastClkCheckTick) < CLK_CHECK_INT) {
		return;
	}

	lastClkCheckTick = getTick();
	DateTime::Model now;
	auto clockOk = clock.now(now);

	if (clockOk && DateTime{now} >= nextLogTime) {
		log(getLoggableString(now));
		nextLogTime = DateTime{now} + minuteInt();
	} else if (!clockOk && backupNeedToLogCheck()) {
			log({"Clock Error"});
	}
}

template <typename FileWriter>
void Logger<FileWriter>::log(const LoggableString& clockStamp) {
	LoggableString wdStr{};

	if (lastReading.statusOk) {
		wdStr = getLoggableString(lastReading.data);
	} else {
		snprintf(wdStr.data(), wdStr.size(), "%s", "Sensor Error");
	}

	char buf[60];
	snprintf(buf, sizeof(buf), "%s - %s\n", clockStamp.data(), wdStr.data());
	fileWriter.writeToFile("log.txt", buf);
	lastLogTick = getTick();
}

template <typename FileWriter>
void Logger<FileWriter>::setConfig(const LogConfig& l) {
	if (l != logConfig) {
		logConfig = l;

		// Log next update if config is enabled
		if (logConfig.enabled) {
			DateTime::Model now;
			if (clock.now(now))
				nextLogTime.setData(now);
			else
				logConfig.enabled = false; // disable if clock is faulty
		}
	}
}

template <typename FileWriter>
bool Logger<FileWriter>::backupNeedToLogCheck() const {
	auto miliInterval = hoursToMili(logConfig.hourInt) + minToMili(logConfig.minInt);
	return timeElapsed(lastLogTick) >= miliInterval;
}


#endif /* SERVICES_INC_LOGGER_H_ */
