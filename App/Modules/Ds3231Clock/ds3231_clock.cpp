#include "ds3231_clock.h"
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

namespace {
	constexpr uint8_t TIME_MODE_BIT_MASK = 1 << 6;
	constexpr uint8_t CENTURY_BIT_MASK = 1 << 7;
}

void Ds3231Clock::runHealthCheck() {
	uint8_t buffer;

	if (receiveData(&buffer, 1) == HAL_OK) {
		status = CLOCK_STATUS::OK;
	} else {
		status = CLOCK_STATUS::RECEIVE_ERROR;
	}
}

bool Ds3231Clock::isValidDateTime(const DateTime& dt) {
	// Currently checks for register correctness only, not calendar correctness
	return
		dt.second <= 59 &&
		dt.minute <= 59 &&
		dt.hour <= 23 &&
		dt.day >= 1 && dt.day <= 7 &&
		dt.date >= 1 && dt.day <= 31 &&
		dt.month >= 1 && dt.month <= 12;
}

CLOCK_STATUS Ds3231Clock::setDateTime(const DateTime& dt) {
	if (!isValidDateTime(dt)) {
		return CLOCK_STATUS::INVALID_INPUT;
	}

	uint8_t buffer[8] = {0};
	// buffer[0] is the register pointer, which we want to leave at 0x00
	buffer[1] = decimalToBcd(dt.second);
	buffer[2] = decimalToBcd(dt.minute);
	buffer[3] = decimalToBcd(dt.hour);
	buffer[4] = decimalToBcd(dt.day);
	buffer[5] = decimalToBcd(dt.date);
	buffer[6] = (dt.year / 100) << 7 | decimalToBcd(dt.month); // bit 7 of month register = century
	buffer[7] = decimalToBcd(dt.year);

	status = sendData(buffer, 8) == HAL_OK
		? CLOCK_STATUS::OK
		: CLOCK_STATUS::SEND_ERROR;

	return status;
}

CLOCK_STATUS Ds3231Clock::currentDateTime(DateTime& dt) {
	uint8_t buffer[7];

	// Set the register pointer to 0x00 and then read 7 bytes. Check that both succeed
	if (sendData(0x00, 1) != HAL_OK) {
		status = CLOCK_STATUS::SEND_ERROR;
	} else if (receiveData(buffer, 7) != HAL_OK) {
		status = CLOCK_STATUS::RECEIVE_ERROR;
	} else {
		status = CLOCK_STATUS::OK;

		dt.second = bcdToDecimal(buffer[0]);
		dt.minute = bcdToDecimal(buffer[1]);
		dt.hour = bcdToDecimal(buffer[2] & ~TIME_MODE_BIT_MASK); // ignore 12/24 hour bit
		dt.day = bcdToDecimal(buffer[3]);
		dt.date = bcdToDecimal(buffer[4]);
		dt.month = bcdToDecimal(buffer[5] & ~CENTURY_BIT_MASK); // ignore century bit
		dt.year = bcdToDecimal(buffer[6]);

		// Check century in case I need to run this program in the year 2108
		if (buffer[5] & CENTURY_BIT_MASK) {
			dt.year += 100;
		}
	}

	return status;
}



HAL_StatusTypeDef Ds3231Clock::sendData(uint8_t* data, uint8_t numBytes) {
	return HAL_I2C_Master_Transmit(hi2c, ADDRESS, data, numBytes, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Ds3231Clock::receiveData(uint8_t* buffer, uint8_t numBytes) {
	return HAL_I2C_Master_Receive(hi2c, ADDRESS, buffer, numBytes, HAL_MAX_DELAY);
}

uint8_t Ds3231Clock::decimalToBcd(uint8_t decimal) {
	return (decimal / 10) << 4 | decimal % 10;
}

uint8_t Ds3231Clock::bcdToDecimal(uint8_t bcd) {
	// extract high nibble, shift it right 4, and multiply by 10 for tens place
	uint8_t tens = ((bcd & 0xF0) >> 4) * 10;

	// extract low nibble for ones place
	uint8_t ones = (bcd & 0x0F);

	return tens + ones;
}

