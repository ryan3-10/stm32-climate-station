#ifndef DRIVERS_DS3231_DS3231_H_
#define DRIVERS_DS3231_DS3231_H_

#include "health_checkable.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

class Ds3231 {
public:
	enum class Status : uint8_t {
		Ok,
		SendError,
		ReceiveError
	};

	Status currentDateTime(uint8_t* outBuffer);
	Status setDateTime(uint8_t* inBuffer);
	Status getStatus() { return status; }
	void init(I2C_HandleTypeDef* h) { hi2c = h; }

private:
	HAL_StatusTypeDef sendData(uint8_t* data, uint8_t numBytes);
	HAL_StatusTypeDef receiveData(uint8_t* buffer, uint8_t numBytes);
	uint8_t decimalToBcd(uint8_t decimal);
	uint8_t bcdToDecimal(uint8_t bcd);

	static constexpr uint8_t ADDRESS = 0x68 << 1; // 7-bit address
	I2C_HandleTypeDef* hi2c;
	Status status;

	enum Regs : uint8_t {
		Second = 0,
		Minute,
		Hour,
		Day,
		Date,
		Month,
		Year
	};
};

#endif /* DRIVERS_DS3231_DS3231_H_ */
