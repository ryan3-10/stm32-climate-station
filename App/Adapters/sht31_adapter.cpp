#include "sht31_adapter.h"
#include "weather_sensor.h"

void Sht31Adapter::runHealthCheck() {
	float dummy;
	sht31.getTempFAndHum(dummy, dummy);
}

bool Sht31Adapter::getReading(WeatherData& wd) {
	return sht31.getTempFAndHum(wd.temp, wd.hum) == Sht31Sensor::Status::Ok;
}
