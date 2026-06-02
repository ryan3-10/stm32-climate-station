#ifndef WEATHER_STATION_H_
#define WEATHER_STATION_H_

#include "data_structs.h"
#include "weather_sensor.h"
#include <stdint.h>

class WeatherStation {
public:
	WeatherStation(IWeatherSensor& s) : sensor(s) {}
	void update();
	uint32_t getLastReadTime() const { return lastReadTime; }
	WeatherData read() { return data; }
private:
	bool noiseDetected(const WeatherData& d1, const WeatherData& d2) const;

	IWeatherSensor& sensor;
	uint32_t lastReadTime = 0;
	WeatherData data;
};



#endif /* WEATHER_DATA_H_ */
