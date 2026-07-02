#include "ds3231_clock.h"
#include <array>
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

namespace {
	constexpr uint8_t TIME_MODE_BIT = 6;
	constexpr uint8_t CENTURY_BIT = 7;
	constexpr uint8_t TIME_MODE_MASK = 1 << TIME_MODE_BIT;
	constexpr uint8_t CENTURY_MASK = 1 << CENTURY_BIT;
}

Ds3231Clock::Status Ds3231Clock::setDateTime(uint8_t* inBuffer) {
	uint8_t rawBuffer[8] = {0};

	// buffer[0] is the register pointer, which we want to leave at 0x00
	for (uint8_t i = 1; i < sizeof(rawBuffer); ++i) {
		rawBuffer[i] = decimalToBcd(inBuffer[i - 1]);
	}

	// bit 7 of month register = century
	rawBuffer[Regs::Month] |= (inBuffer[Regs::Year] / 100) << CENTURY_BIT;

	status = sendData(rawBuffer, sizeof(rawBuffer)) == HAL_OK
		? Status::Ok
		: Status::SendError;

	return status;
}

Ds3231Clock::Status Ds3231Clock::currentDateTime(uint8_t* outBuffer) {
	uint8_t rawBuffer[7];

	// Set the register pointer to 0x00 and then read 7 bytes. Check that both succeed
	if (sendData(0x00, 1) != HAL_OK) {
		status = Status::SendError;
	} else if (receiveData(rawBuffer, sizeof(rawBuffer)) != HAL_OK) {
		status = Status::ReceiveError;
	} else {
		status = Status::Ok;

		// Need to ignore 12/24 hour bit, and century bit
		std::array<uint8_t, 7> masks {0, 0, TIME_MODE_MASK, 0, 0, CENTURY_MASK, 0};

		for (uint8_t i = 0; i < sizeof(rawBuffer); ++i) {
			outBuffer[i] = bcdToDecimal(rawBuffer[i] & ~masks[i]);
		}

		// Check century bit in case I need to run this program in the year 2108
		if (rawBuffer[Regs::Month] & CENTURY_MASK) {
			outBuffer[Regs::Year] += 100;
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

