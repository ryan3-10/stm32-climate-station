#ifndef EXTERNAL_DRIVERS_SHT31_SENSOR_H_
#define EXTERNAL_DRIVERS_SHT31_SENSOR_H_

#include "data_structs.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

enum class SENSOR_STATUS : uint8_t;

class Sht31Sensor {
public:
	Sht31Sensor() = default;
	SENSOR_STATUS getTempFAndHum(float& temp, float& hum);
	void init(I2C_HandleTypeDef* h) { hi2c = h; }


private:
	float rawToHumidity(uint8_t byte1, uint8_t byte2) const;
	float rawToTempF(uint8_t byte1, uint8_t byte2) const;
	HAL_StatusTypeDef requestData();
	HAL_StatusTypeDef receiveData(uint8_t* buffer);

	static constexpr uint8_t ADDRESS = 0x44 << 1; // 7-bit address
	uint8_t READ_COMMAND[2] = {0x2C, 0x06}; // Single shot, high repeat, clock stretch enabled
	I2C_HandleTypeDef* hi2c;
};

enum class SENSOR_STATUS : uint8_t {
	OK,
	SEND_ERROR,
	RECEIVE_ERROR
};

#endif /* EXTERNAL_DRIVERS_SHT31_SENSOR_H_ */
