#ifndef MODULES_DS3231CLOCK_DS3231_CLOCK_H_
#define MODULES_DS3231CLOCK_DS3231_CLOCK_H_

#include "health_checkable.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

struct DateTime;

enum class CLOCK_STATUS : uint8_t {
	OK,
	INVALID_INPUT,
	SEND_ERROR,
	RECEIVE_ERROR
};

class Ds3231Clock : public HealthCheckable {
public:
	CLOCK_STATUS currentDateTime(DateTime& dt);
	CLOCK_STATUS setDateTime(const DateTime& dt);
	CLOCK_STATUS getStatus() { return status; }
	void init(I2C_HandleTypeDef* h) { hi2c = h; }
	const char* getErrorCode() const override { return "Cl"; }
	bool isOk() const override { return status == CLOCK_STATUS::OK; }
	void runHealthCheck() override;

private:
	bool isValidDateTime(const DateTime& dt);
	HAL_StatusTypeDef sendData(uint8_t* data, uint8_t numBytes);
	HAL_StatusTypeDef receiveData(uint8_t* buffer, uint8_t numBytes);
	uint8_t decimalToBcd(uint8_t decimal);
	uint8_t bcdToDecimal(uint8_t bcd);

	static constexpr uint8_t ADDRESS = 0x68 << 1; // 7-bit address
	I2C_HandleTypeDef* hi2c;
	CLOCK_STATUS status;
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
