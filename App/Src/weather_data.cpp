#include "sht31_sensor.h"
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>
#include <weather_data.h>

namespace {
constexpr float NOISE_THRESHOLD = 1.0f;
constexpr uint32_t readWriteInterval = 1000;
}

WeatherData::WeatherData(Sht31Sensor& s) : sensor(s) {

}

bool WeatherData::meaningfulChange(SENSOR_DATA newData) const {
	return (
		newData.statusOk != statusOk ||
		abs(newData.temperature - temperature) >= NOISE_THRESHOLD ||
		abs(newData.humidity - humidity) >= NOISE_THRESHOLD
	);
}

float WeatherData::getHumidity() const {
	return humidity;
}

float WeatherData::getTemperature() const {
	return temperature;
}

void WeatherData::notify() {
	for (uint8_t i = 0; i < observerCount; ++i) {
		observers.at(i)->update(temperature, humidity, statusOk);
	}
}

void WeatherData::setValues(SENSOR_DATA newData) {
	temperature = newData.temperature;
	humidity = newData.humidity;
	statusOk = newData.statusOk;
}

void WeatherData::update() {
	SENSOR_DATA newData = sensor.getLiveData();

	if (meaningfulChange(newData)) {
		setValues(newData);
		notify();
	}
	lastUpdate = HAL_GetTick();
}

uint32_t WeatherData::getLastUpdate() const {
	return lastUpdate;
}
