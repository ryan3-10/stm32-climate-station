#ifndef EXTERNAL_DRIVERS_SHT31_SENSOR_H_
#define EXTERNAL_DRIVERS_SHT31_SENSOR_H_

#include "data_structs.h"
#include "observer.h"
#include <stdint.h>
#include <stm32f4xx_hal.h>

class Sht31Sensor : public Subject {
public:
	Sht31Sensor() = default;
	void update();
	void init(I2C_HandleTypeDef* h) { hi2c = h; }
	void notifyObservers() const override;
	uint32_t timeSinceLastRead();


private:
	WeatherData weatherData;
	I2C_HandleTypeDef* hi2c;
	uint32_t lastReadTime = 0;

	float rawToHumidity(uint8_t byte1, uint8_t byte2) const;
	float rawToTemperature(uint8_t byte1, uint8_t byte2) const;

	HAL_StatusTypeDef requestData();
	HAL_StatusTypeDef receiveData(uint8_t* buffer);
};

#endif /* EXTERNAL_DRIVERS_SHT31_SENSOR_H_ */
