#include "sht31_sensor.h"
#include <stm32f4xx_hal.h>

namespace {
	constexpr uint8_t ADDRESS = 0x44 << 1;
	uint8_t READ_COMMAND[2] = {0x2C, 0x06}; // Single shot, high repeat, clock stretch enabled
}

float Sht31Sensor::rawToHumidity(uint8_t rawByte1, uint8_t rawByte2) const {
	uint16_t rawHumidity = (rawByte1 << 8) | rawByte2;
	return 100 * rawHumidity / 65535.0f;
}

float Sht31Sensor::rawToTemperature(uint8_t rawByte1, uint8_t rawByte2) const {
	uint16_t rawTemp = (rawByte1 << 8) | rawByte2;
	return -49 + (315.0f * rawTemp / 65535.0f);
}

const WeatherData Sht31Sensor::read() {
	uint8_t data[6];
	WeatherData result { .statusOk = true };

	if (requestData() != HAL_OK || receiveData(data) != HAL_OK) {
		result.statusOk = false;
	}

	if (result.statusOk) {
		result.temp = rawToTemperature(data[0], data[1]);
		result.hum = rawToHumidity(data[3], data[4]);
	}

	return result;
}

HAL_StatusTypeDef Sht31Sensor::requestData() {
	return HAL_I2C_Master_Transmit(hi2c, ADDRESS, READ_COMMAND, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Sht31Sensor::receiveData(uint8_t* buffer) {
	return HAL_I2C_Master_Receive(hi2c, ADDRESS, buffer, 6, HAL_MAX_DELAY);
}



