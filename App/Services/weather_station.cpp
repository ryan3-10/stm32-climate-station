#include "time_service.h"
#include "weather_station.h"

void WeatherStation::update() {
	lastRead.statusOk = sensor.getTempFAndHum(
			lastRead.data.temp,
			lastRead.data.hum
		) == Sht31Sensor::Status::Ok;

	lastReadTime = getTick();
}

void WeatherStation::notifyObservers() const {
	for (uint8_t i = 0; i < count; ++i) {
		observers.at(i)->onWeatherUpdate(lastRead);
	}
}

uint32_t WeatherStation::timeSinceLastRead() {
	return timeElapsed(lastReadTime);
}
