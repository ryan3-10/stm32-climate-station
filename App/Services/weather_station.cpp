#include "utils.h"
#include "weather_station.h"
#include <cmath>

void WeatherStation::update() {
	if (Utils::timeElapsed(lastReadTime) < INTERVAL) {
		return;
	}

	auto newRead = getReading();

	if (significantDiff(newRead)) {
		lastRead = newRead;
		notifyObservers();
	}
}

// An initial forced read to avoid waiting INTERVAL before first read
void WeatherStation::init() {
	lastRead = getReading();
	notifyObservers();
}

void WeatherStation::notifyObservers() const {
	for (uint8_t i = 0; i < count; ++i) {
		observers.at(i)->onWeatherUpdate(lastRead);
	}
}

SensorRead WeatherStation::getReading() {
	SensorRead newRead {};
	newRead.statusOk = sensor.getWeather(newRead.data);
	lastReadTime = Utils::getTick();
	return newRead;
}

bool WeatherStation::significantDiff(const SensorRead& newRead) {
	// If sensor was and still is in an error state, ignore everything else
	if (!(lastRead.statusOk || newRead.statusOk)) {
		return false;
	}

	// Return true if statusOk has changed, or if temp or hum have changed by more than
	// NOISE_THRESHOLD
	return
		lastRead.statusOk != newRead.statusOk ||
		std::abs(lastRead.data.temp - newRead.data.temp) > NOISE_THRESHOLD ||
		std::abs(lastRead.data.hum - newRead.data.hum) > NOISE_THRESHOLD;
}
