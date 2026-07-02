#include "observer.h"
#include <stdint.h>

#include "sht31.h"
#ifndef SERVICES_WEATHER_STATION_H_
#define SERVICES_WEATHER_STATION_H_

class WeatherStation : public Subject<WeatherObserver> {
public:
	WeatherStation(Sht31& s) : sensor(s) {}
	void update();
	void notifyObservers() const override;
	uint32_t timeSinceLastRead();

private:
	Sht31& sensor;
	SensorRead lastRead;
	uint32_t lastReadTime = 0;
};

#endif /* SERVICES_WEATHER_STATION_H_ */
