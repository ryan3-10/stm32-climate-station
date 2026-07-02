#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "clock.h"
#include "config_models.h"
#include "observer.h"
#include "weather_models.h"
#include "file_manager.h"
#include <stdio.h>
#include <string.h>
#include <utils.h>

class Logger : public WeatherObserver, public SettingsObserver {
public:
	Logger(const LogConfig& l, IClock& c, FileManager& fm)
		: logConfig(l)
		, clock(c)
		, fileManager(fm)
	{}

	~Logger() = default;

	void init();

	template <typename FileWriter>
	void log(FileWriter writer) {
		char dtBuf[25];
		DateTime dt;

		if (clock.now(dt)) {
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
		if (lastReading.statusOk) {
			snprintf(
				weatherBuf,
				sizeof(weatherBuf),
				"%.1fF %.1f%%",
				lastReading.data.temp, lastReading.data.hum
			);
		} else {
			strncpy(weatherBuf, "Sensor Error", sizeof(weatherBuf) - 1);
		}

		char masterBuf[60];
		snprintf(masterBuf, sizeof(masterBuf), "%s %s\n", dtBuf, weatherBuf);
		writer.writeToFile("log.txt", masterBuf);
		lastLogTime = Utils::getTick();
	}

	void setConfig(const LogConfig& l) { logConfig = l; }
	void onSettingsChange(const Settings& settings) override;
	void onWeatherUpdate(const SensorRead& reading) override { lastReading = reading; }
	bool needsToLog() const;

private:
	LogConfig logConfig;
	IClock& clock;
	FileManager& fileManager;
	uint32_t lastLogTime;
	SensorRead lastReading;
};



#endif /* SERVICES_INC_LOGGER_H_ */
