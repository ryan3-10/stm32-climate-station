#include "sht31_sensor.h"
#include "weather_station.h"
#include <cmath>
#include <stdint.h>
#include <stm32f4xx_hal.h>

void WeatherStation::update() {
	const auto newData = sensor.read();

	if (!noiseDetected(newData, data)) {
		data = newData;
	}

	lastReadTime = HAL_GetTick();
}

bool WeatherStation::noiseDetected(const WeatherData& d1, const WeatherData& d2) const {
	constexpr float NOISE_THRESHOLD = 0.0f;

	// If statusOk was and still is false, ignore potential garbage values
	if (!d1.statusOk && !d2.statusOk) {
		return true;
	}

	return (
		d1.statusOk == d2.statusOk &&
		abs(d1.temp - d2.temp) <= NOISE_THRESHOLD &&
		abs(d1.hum - d2.hum) <= NOISE_THRESHOLD
	);
}
