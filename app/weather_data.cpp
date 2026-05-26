#include "sht31_sensor.h"
#include "weather_data.h"
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

constexpr static uint32_t readWriteInterval = 1000;

WeatherData::WeatherData(Sht31Sensor& s) : sensor(s) {
	readWriteData();
}

float WeatherData::getTemperature() {
	return temperature;
}

float WeatherData::getHumidity() {
	return humidity;
}

void WeatherData::readWriteData() {
	sensor.updateWeatherValues(temperature, humidity);
	lastReadWrite = HAL_GetTick();
}

void WeatherData::update() {
	if (HAL_GetTick() - lastReadWrite >= readWriteInterval) {
		readWriteData();
	}
}
