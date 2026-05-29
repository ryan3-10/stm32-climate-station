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

WeatherStation::WeatherStation(Sht31Sensor& s) : sensor(s) {

}

bool WeatherStation::meaningfulChange(SENSOR_DATA newData) const {
	// If statusOk was and still is false, ignore potential garbage values in weather data
	if (!newData.statusOk && !statusOk) {
		return false;
	}

	return (
		newData.statusOk != statusOk ||
		abs(newData.temperature - temperature) >= NOISE_THRESHOLD ||
		abs(newData.humidity - humidity) >= NOISE_THRESHOLD
	);
}

float WeatherStation::getHumidity() const {
	return humidity;
}

float WeatherStation::getTemperature() const {
	return temperature;
}

void WeatherStation::notify() {
	for (uint8_t i = 0; i < observerCount; ++i) {
		observers.at(i)->update(temperature, humidity, statusOk);
	}
}

void WeatherStation::setValues(SENSOR_DATA newData) {
	temperature = newData.temperature;
	humidity = newData.humidity;
	statusOk = newData.statusOk;
}

void WeatherStation::update() {
	SENSOR_DATA newData = sensor.getLiveData();

	if (meaningfulChange(newData)) {
		setValues(newData);
		notify();
	}
	lastUpdate = HAL_GetTick();
}

uint32_t WeatherStation::getLastUpdate() const {
	return lastUpdate;
}
