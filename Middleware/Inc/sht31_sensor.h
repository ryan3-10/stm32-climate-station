#ifndef EXTERNAL_DRIVERS_SHT31_SENSOR_H_
#define EXTERNAL_DRIVERS_SHT31_SENSOR_H_

#include <stm32f4xx_hal.h>

class Sht31Sensor {
private:
	I2C_HandleTypeDef* hi2c;

	float rawToHumidity(uint8_t byte1, uint8_t byte2);
	float rawToTemperature(uint8_t byte1, uint8_t byte2);

public:
	Sht31Sensor(I2C_HandleTypeDef* h);
	Sht31Sensor(const Sht31Sensor&) = delete;
	Sht31Sensor& operator=(const Sht31Sensor&) = delete;
	Sht31Sensor(Sht31Sensor&&) = delete;
	Sht31Sensor& operator=(Sht31Sensor&&) = delete;

	void updateWeatherValues(float& temperature, float& humidity);
};

#endif /* EXTERNAL_DRIVERS_SHT31_SENSOR_H_ */
