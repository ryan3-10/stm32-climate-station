#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "clock.h"
#include "data_structs.h"
#include "file_manager.h"
#include "observer.h"

class Logger : public WeatherObserver, public SettingsObserver {
public:
	Logger(const LogConfig& l, IClock& c, FileManager& fm)
		: logConfig(l)
		, clock(c)
		, fileManager(fm)
	{}

	~Logger() = default;

	void init();
	void log();
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
