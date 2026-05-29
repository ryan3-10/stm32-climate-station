#include "sht31_sensor.h"
#include "weather_station.h"
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

namespace {
	constexpr float NOISE_THRESHOLD = 1.0f;
	constexpr uint32_t readWriteInterval = 1000;
}

bool WeatherStation::meaningfulChange(SENSOR_DATA newData) const {
	// If statusOk was and still is false, ignore potential garbage values in weather data
	if (!newData.statusOk && !data.statusOk) {
		return false;
	}

	return (
		newData.statusOk != data.statusOk ||
		abs(newData.temperature - data.temperature) >= NOISE_THRESHOLD ||
		abs(newData.humidity - data.humidity) >= NOISE_THRESHOLD
	);
}

void WeatherStation::setValues(SENSOR_DATA newData) {
	data.statusOk = newData.statusOk;
	data.temperature = newData.temperature;
	data.humidity = newData.humidity;
}

void WeatherStation::update() {
	SENSOR_DATA newData = sensor.getLiveData();

	if (meaningfulChange(newData)) {
		setValues(newData);
		notify();
	}
	lastUpdate = HAL_GetTick();
}
