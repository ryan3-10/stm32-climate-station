#ifndef MODULES_DS3231CLOCK_DS3231_CLOCK_H_
#define MODULES_DS3231CLOCK_DS3231_CLOCK_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

struct DateTime;
enum CLOCK_STATUS : uint8_t;

class Ds3231Clock {
public:
	CLOCK_STATUS currentDateTime(DateTime& dt);
	CLOCK_STATUS setDateTime(DateTime dt);
	void init(I2C_HandleTypeDef* h) { hi2c = h; }

private:
	bool isValidDateTime(DateTime dt);
	HAL_StatusTypeDef sendData(uint8_t* data, uint8_t numBytes);
	HAL_StatusTypeDef receiveData(uint8_t* buffer, uint8_t numBytes);
	uint8_t decimalToBcd(uint8_t decimal);
	uint8_t bcdToDecimal(uint8_t bcd);

	static constexpr uint8_t ADDRESS = 0x68 << 1; // 7-bit address
	I2C_HandleTypeDef* hi2c;
};

enum CLOCK_STATUS : uint8_t {
	OK,
	INVALID_INPUT,
	HARDWARE_ERR
};

struct DateTime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

#endif /* MODULES_DS3231CLOCK_DS3231_CLOCK_H_ */
