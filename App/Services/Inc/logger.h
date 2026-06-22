#ifndef SERVICES_INC_LOGGER_H_
#define SERVICES_INC_LOGGER_H_

#include "data_structs.h"
#include "observer.h"
#include <fatfs.h>

class Logger : public WeatherObserver, public SettingsObserver {
public:
	Logger(const LogConfig& l) : logConfig(l) {}
	~Logger() = default;

	void log();
	void setConfig(const LogConfig& l) { logConfig = l; }
	void onSettingsChange(const Settings& settings) override;
	void onWeatherUpdate(const WeatherData& weather) override { cachedWeather = weather; }
	bool needsToLog() const;
	void init();

private:
	void createFileIfNotExist(const char* fileName);
	void writeToFile(const char* fileName, const char* text);

	LogConfig logConfig;
	uint32_t lastLogTime;
	WeatherData cachedWeather;
	FATFS FatFs; 	//Fatfs handle
};



#endif /* SERVICES_INC_LOGGER_H_ */
