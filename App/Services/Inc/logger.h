#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "data_structs.h"
#include "file_manager.h"
#include "observer.h"

class Logger : public WeatherObserver, public SettingsObserver {
public:
	Logger(const LogConfig& l) : logConfig(l) {}
	~Logger() = default;

	void init();
	void log();
	void setConfig(const LogConfig& l) { logConfig = l; }
	void onSettingsChange(const Settings& settings) override;
	void onWeatherUpdate(const WeatherData& weather) override { cachedWeather = weather; }
	bool needsToLog() const;

private:
	LogConfig logConfig;
	uint32_t lastLogTime;
	WeatherData cachedWeather;
	FileManager fileManager;
};



#endif /* SERVICES_INC_LOGGER_H_ */
