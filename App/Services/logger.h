#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "clock.h"
#include "config_models.h"
#include "observer.h"
#include "weather_models.h"
#include <stdio.h>
#include <utils.h>

class Logger : public WeatherObserver, public SettingsObserver {
public:
	Logger(const LogConfig& l, IClock& c) : logConfig(l) , clock(c) {}

	template <typename FileWriter>
	void log(FileWriter& writer) {
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
		writer.writeToFile("log.txt", buf);
		lastLogTime = Utils::getTick();
	}

	void setConfig(const LogConfig& l) { logConfig = l; }
	void onSettingsChange(const Settings& settings) override;
	void onWeatherUpdate(const SensorRead& reading) override { lastReading = reading; }
	bool needsToLog() const;

private:
	LogConfig logConfig;
	IClock& clock;
	uint32_t lastLogTime;
	SensorRead lastReading;
};



#endif /* SERVICES_INC_LOGGER_H_ */
