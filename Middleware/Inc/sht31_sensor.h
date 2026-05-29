#ifndef EXTERNAL_DRIVERS_SHT31_SENSOR_H_
#define EXTERNAL_DRIVERS_SHT31_SENSOR_H_

#include <stm32f4xx_hal.h>

struct SENSOR_DATA {
	float humidity;
	float temperature;
	bool statusOk;
};

class Sht31Sensor {
private:
	I2C_HandleTypeDef* hi2c;

	float rawToHumidity(uint8_t byte1, uint8_t byte2);
	float rawToTemperature(uint8_t byte1, uint8_t byte2);

	HAL_StatusTypeDef requestData();
	HAL_StatusTypeDef receiveData(uint8_t* buffer);

public:
	Sht31Sensor(I2C_HandleTypeDef* h);

	SENSOR_DATA getLiveData();
};

#endif /* EXTERNAL_DRIVERS_SHT31_SENSOR_H_ */
