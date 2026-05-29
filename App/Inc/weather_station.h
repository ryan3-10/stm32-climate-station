#ifndef WEATHER_STATION_H_
#define WEATHER_STATION_H_

#include "observer.h"
#include "sht31_sensor.h"
#include <stdint.h>

struct WeatherData {
	bool statusOk;
    float temperature;
    float humidity;
};

class WeatherStation : public Subject {
public:
	WeatherStation(Sht31Sensor& s);
	void update();
	uint32_t getLastUpdate() const;
	const WeatherData& getLiveData() const;

private:
	bool meaningfulChange(SENSOR_DATA newData) const;
	void setValues(SENSOR_DATA newData);

	Sht31Sensor& sensor;
	uint32_t lastUpdate = 0;
	WeatherData data;
};



#endif /* WEATHER_DATA_H_ */
