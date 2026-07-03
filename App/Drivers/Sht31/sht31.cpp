#include "sht31.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

Sht31::Status Sht31::getTempFAndHum(float& temp, float& hum) {
	uint8_t data[6];

	if (requestData() != HAL_OK) {
		status = Status::SendError;
	} else if (receiveData(data) != HAL_OK) {
		status = Status::ReceiveError;
	} else {
		status = Status::Ok;
		temp = rawToTempF(data[0], data[1]);
		hum = rawToHumidity(data[3], data[4]);
	}

	return status;
}

float Sht31::rawToHumidity(uint8_t rawByte1, uint8_t rawByte2) const {
	uint16_t rawHumidity = (rawByte1 << 8) | rawByte2;
	return 100 * rawHumidity / 65535.0f;
}

float Sht31::rawToTempF(uint8_t rawByte1, uint8_t rawByte2) const {
	uint16_t rawTemp = (rawByte1 << 8) | rawByte2;
	return -49 + (315.0f * rawTemp / 65535.0f);
}

HAL_StatusTypeDef Sht31::requestData() {
	return HAL_I2C_Master_Transmit(hi2c, ADDRESS, READ_COMMAND, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Sht31::receiveData(uint8_t* buffer) {
	return HAL_I2C_Master_Receive(hi2c, ADDRESS, buffer, 6, HAL_MAX_DELAY);
}



