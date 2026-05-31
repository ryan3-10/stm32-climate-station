#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct WeatherData {
	bool statusOk = true;
	float temp = 0.0f;
	float hum = 0.0f;
};

struct LogData {
	bool enabled = false;
	uint8_t hourInt = 0;
	uint8_t minInt = 0;
};

struct AlertData {
	bool tempEnabled = false;
	bool humEnabled = false;
	uint16_t maxTemp = 0;
	uint16_t minTemp = 0;
	uint16_t maxHum = 0;
	uint16_t minHum = 0;
};

#endif /* INC_APP_CONFIG_H_ */
