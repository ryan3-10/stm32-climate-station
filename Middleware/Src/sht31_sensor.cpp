#include "sht31_sensor.h"

#include <stdio.h>
#include <stm32f4xx_hal.h>

namespace {
	constexpr uint8_t ADDRESS = 0x44 << 1;
}

Sht31Sensor::Sht31Sensor(I2C_HandleTypeDef* h) : hi2c(h)
{

}

float Sht31Sensor::rawToHumidity(uint8_t rawByte1, uint8_t rawByte2) {
	uint16_t rawHumidity = (rawByte1 << 8) | rawByte2;
	return 100 * rawHumidity / 65535.0f;
}

float Sht31Sensor::rawToTemperature(uint8_t rawByte1, uint8_t rawByte2) {
	uint16_t rawTemp = (rawByte1 << 8) | rawByte2;
	return -49 + (315.0f * rawTemp / 65535.0f);
}

void Sht31Sensor::updateWeatherValues(float& temperature, float& humidity) {
	uint8_t READ_COMMAND[2] = {0x2C, 0x06}; // Single shot, high repeat, clock stretch enabled
	HAL_StatusTypeDef status;
	uint8_t data[6];

	status = HAL_I2C_Master_Transmit(hi2c, ADDRESS, READ_COMMAND, 2, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		printf("Error Tx\n");
		return;
	}

	status = HAL_I2C_Master_Receive(hi2c, ADDRESS, data, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		printf("Error Rx\n");
		return;
	}

	temperature = rawToTemperature(data[0], data[1]);
	humidity = rawToHumidity(data[3], data[4]);
}



