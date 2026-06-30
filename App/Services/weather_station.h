#include "observer.h"
#include "sht31_sensor.h"
#include <stdint.h>

#ifndef SERVICES_WEATHER_STATION_H_
#define SERVICES_WEATHER_STATION_H_

class WeatherStation : public Subject<WeatherObserver> {
public:
	WeatherStation(Sht31Sensor& s) : sensor(s) {}
	void update();
	void notifyObservers() const override;
	uint32_t timeSinceLastRead();

private:
	Sht31Sensor& sensor;
	SensorRead lastRead;
	uint32_t lastReadTime = 0;
};

#endif /* SERVICES_WEATHER_STATION_H_ */
