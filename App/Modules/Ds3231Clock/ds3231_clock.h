#ifndef MODULES_DS3231CLOCK_DS3231_CLOCK_H_
#define MODULES_DS3231CLOCK_DS3231_CLOCK_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

struct DateTime;

class Ds3231Clock {
public:
	DateTime currentDateTime();
	bool setDateTime(DateTime dt);
	void init(I2C_HandleTypeDef* h) { hi2c = h; }

private:
	DateTime rawToDateTime(uint8_t* rawData);
	HAL_StatusTypeDef setRegisterPointer(uint8_t regAddress);
	HAL_StatusTypeDef receiveData(uint8_t* buffer, uint8_t numBytes);

	static constexpr uint8_t ADDRESS = 0x68 << 1; // 7-bit address
	I2C_HandleTypeDef* hi2c;
};

struct DateTime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	bool statusOk;
};

#endif /* MODULES_DS3231CLOCK_DS3231_CLOCK_H_ */
