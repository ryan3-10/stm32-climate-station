#include <weather_station.h>
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

WeatherStation::WeatherStation() {
	readData();
}

float WeatherStation::rawToHumidity(uint8_t rawByte1, uint8_t rawByte2) {
	uint16_t rawHumidity = (rawByte1 << 8) | rawByte2;
	return 100 * rawHumidity / 65535.0f;
}

float WeatherStation::rawToTemperature(uint8_t rawByte1, uint8_t rawByte2) {
	uint16_t rawTemp = (rawByte1 << 8) | rawByte2;
	return -49 + (315.0f * rawTemp / 65535.0f);
}

float WeatherStation::getTemperature() {
	return temperature;
}

float WeatherStation::getHumidity() {
	return humidity;
}

void WeatherStation::readData() {
	static const uint8_t SHT31_ADDR = 0x44 << 1; // use 8-bit address
	static uint8_t READ_COMMAND[2] = {0x2C, 0x06}; // Single shot, high repeat, clock stretch enabled
	HAL_StatusTypeDef status;
	I2C_HandleTypeDef hi2c1;
	uint8_t data[6];

	status = HAL_I2C_Master_Transmit(&hi2c1, SHT31_ADDR, READ_COMMAND, 2, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		printf("Error Tx\n");
		return;
	}

	status = HAL_I2C_Master_Receive(&hi2c1, SHT31_ADDR, data, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		printf("Error Rx\n");
		return;
	}

	temperature = rawToTemperature(data[0], data[1]);
	humidity = rawToHumidity(data[3], data[4]);
	lastRead = HAL_GetTick();
}

void WeatherStation::update() {
	if (HAL_GetTick() - lastRead >= readInterval) {
		readData();
	}
}

WeatherStation& WeatherStation::getInstance() {
	static WeatherStation instance;
	return instance;
}
