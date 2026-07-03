#include <sht31_sensor.h>
#include "weather_sensor.h"

void Sht31Sensor::runHealthCheck() {
	float dummy;
	sht31.getTempFAndHum(dummy, dummy);
}

bool Sht31Sensor::getWeather(WeatherData& wd) {
	return sht31.getTempFAndHum(wd.temp, wd.hum) == Sht31::Status::Ok;
}
