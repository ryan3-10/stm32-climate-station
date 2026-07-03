#include "observer.h"
#include "weather_sensor.h"
#include <stdint.h>

#ifndef SERVICES_WEATHER_STATION_H_
#define SERVICES_WEATHER_STATION_H_

class WeatherStation : public Subject<WeatherObserver> {
public:
	WeatherStation(IWeatherSensor& s) : sensor(s) {}
	void update();
	void init();

private:
	void notifyObservers() const override;
	bool significantDiff(const SensorRead& newRead);
	SensorRead getReading();

	static constexpr uint32_t INTERVAL = 1000;
	static constexpr float NOISE_THRESHOLD = 0.3f;
	IWeatherSensor& sensor;
	SensorRead lastRead {};
	uint32_t lastReadTime = 0;
};

#endif /* SERVICES_WEATHER_STATION_H_ */
