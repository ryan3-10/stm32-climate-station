#ifndef WEATHER_STATION_H_
#define WEATHER_STATION_H_

#include "data_structs.h"
#include "observer.h"
#include "sht31_sensor.h"
#include <stdint.h>

class WeatherStation : public Subject {
public:
	WeatherStation(Sht31Sensor& s) : sensor(s) {}
	void update();
	uint32_t getLastReadTime() const { return lastReadTime; }

private:
	bool noiseDetected(const WeatherData& d1, const WeatherData& d2) const;

	Sht31Sensor& sensor;
	uint32_t lastReadTime = 0;
	WeatherData data;
};



#endif /* WEATHER_DATA_H_ */
