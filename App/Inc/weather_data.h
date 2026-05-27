#ifndef WEATHER_DATA_H_
#define WEATHER_DATA_H_

#include "sht31_sensor.h"
#include <stdint.h>

class WeatherData {
private:
	float humidity;
	uint32_t lastReadWrite;
	Sht31Sensor& sensor;
	float temperature;

	void readWriteData();

public:
	WeatherData(Sht31Sensor& s);
	WeatherData(const WeatherData&) = delete;
	WeatherData& operator=(const WeatherData&) = delete;
	WeatherData(WeatherData&&) = delete;
	WeatherData& operator=(WeatherData&&) = delete;

	float getTemperature();
	float getHumidity();
	void update();
};



#endif /* WEATHER_DATA_H_ */
