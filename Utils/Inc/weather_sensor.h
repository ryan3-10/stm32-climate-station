#ifndef INC_WEATHER_SENSOR_H_
#define INC_WEATHER_SENSOR_H_

#include "data_structs.h"

class IWeatherSensor {
public:
	virtual const WeatherData read() = 0;
};


#endif /* INC_WEATHER_SENSOR_H_ */
