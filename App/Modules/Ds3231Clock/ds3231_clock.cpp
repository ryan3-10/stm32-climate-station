#include "ds3231_clock.h"
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

bool Ds3231Clock::setDateTime(DateTime dt) {
	uint8_t buffer[8] = {0};
	buffer[1] |= (dt.second / 10) << 4;
	buffer[1] |= (dt.second % 10) << 0;
	buffer[2] |= (dt.minute / 10) << 4;
	buffer[2] |= (dt.minute % 10) << 0;

	if (dt.hour >= 20) {
		buffer[3] |= 1 << 5;
	} else if (dt.hour >= 10) {
		buffer[3] |= 1 << 4;
	}

	buffer[3] |= (dt.hour % 10) << 0;
	buffer[4] |= (dt.day) << 0;
	buffer[5] |= (dt.date / 10) << 4;
	buffer[5] |= (dt.date % 10) << 0;
	buffer[6] |= (dt.year / 100) << 7;
	buffer[6] |= (dt.month / 10) << 4;
	buffer[6] |= (dt.month % 10) << 0;
	buffer[7] |= (dt.year / 10) << 4;
	buffer[7] |= (dt.year % 10) << 0;

	return HAL_I2C_Master_Transmit(hi2c, ADDRESS, buffer, 8, HAL_MAX_DELAY) == HAL_OK;
}

DateTime Ds3231Clock::currentDateTime() {
	uint8_t buffer[7];

	if (setRegisterPointer(0x00) != HAL_OK || receiveData(buffer, 7) != HAL_OK) {
		return DateTime{ .statusOk = false };
	}

	return rawToDateTime(buffer);
}

DateTime Ds3231Clock::rawToDateTime(uint8_t* rawData) {
	for (uint8_t i = 0; i < 7; ++i) {
		printf("%u: 0X%02X\n", i, rawData[i]);
	}

	return DateTime{};
}

HAL_StatusTypeDef Ds3231Clock::setRegisterPointer(uint8_t regAddress) {
	return HAL_I2C_Master_Transmit(hi2c, ADDRESS, &regAddress, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Ds3231Clock::receiveData(uint8_t* buffer, uint8_t numBytes) {
	return HAL_I2C_Master_Receive(hi2c, ADDRESS, buffer, numBytes, HAL_MAX_DELAY);
}


