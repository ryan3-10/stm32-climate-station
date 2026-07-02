#include "utils.h"
#include "weather_station.h"

void WeatherStation::update() {
	lastRead.statusOk = sensor.getTempFAndHum(
			lastRead.data.temp,
			lastRead.data.hum
		) == Sht31::Status::Ok;

	lastReadTime = Utils::getTick();
}

void WeatherStation::notifyObservers() const {
	for (uint8_t i = 0; i < count; ++i) {
		observers.at(i)->onWeatherUpdate(lastRead);
	}
}

uint32_t WeatherStation::timeSinceLastRead() {
	return Utils::timeElapsed(lastReadTime);
}
