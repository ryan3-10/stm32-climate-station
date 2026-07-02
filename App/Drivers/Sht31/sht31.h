#ifndef EXTERNAL_DRIVERS_SHT31_SENSOR_H_
#define EXTERNAL_DRIVERS_SHT31_SENSOR_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

class Sht31 {
public:
	enum class Status : uint8_t {
		Ok,
		SendError,
		ReceiveError
	};

	Status getTempFAndHum(float& temp, float& hum);
	void init(I2C_HandleTypeDef* h) { hi2c = h; }
	Status getStatus() { return status; }

private:
	float rawToHumidity(uint8_t byte1, uint8_t byte2) const;
	float rawToTempF(uint8_t byte1, uint8_t byte2) const;
	HAL_StatusTypeDef requestData();
	HAL_StatusTypeDef receiveData(uint8_t* buffer);

	Status status;
	static constexpr uint8_t ADDRESS = 0x44 << 1; // 7-bit address
	uint8_t READ_COMMAND[2] = {0x2C, 0x06}; // Single shot, high repeat, clock stretch enabled
	I2C_HandleTypeDef* hi2c;
};

#endif /* EXTERNAL_DRIVERS_SHT31_SENSOR_H_ */
