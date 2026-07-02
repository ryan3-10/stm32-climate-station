#ifndef INTERFACES_WEATHER_SENSOR_H_
#define INTERFACES_WEATHER_SENSOR_H_

#include "data_structs.h"

class IWeatherSensor {
public:
	virtual ~IWeatherSensor() = default;
	virtual bool getReading(WeatherData& wd) = 0;
};


#endif /* INTERFACES_WEATHER_SENSOR_H_ */
