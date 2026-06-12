#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct WeatherData {
	bool statusOk = true;
	float temp = 0.0f;
	float hum = 0.0f;
};

struct LogConfig {
	uint16_t hourInt = 0;
	uint16_t minInt = 0;
	bool enabled = false;
};

struct HumAlertConfig {
	uint16_t maxHum = 0;
	uint16_t minHum = 0;
	bool enabled;
};

struct TempAlertConfig {
	uint16_t maxTemp = 0;
	uint16_t minTemp = 0;
	bool enabled = false;
};

struct Settings {
	LogConfig log{};
	TempAlertConfig tempAlert{};
	HumAlertConfig humAlert{};
};


#endif /* INC_APP_CONFIG_H_ */
