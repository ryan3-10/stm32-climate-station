#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct CONFIG {
	bool enabled = false;

	union {
		uint8_t hourInterval = 0;
		uint8_t maxHum;
		int16_t maxTemp;
	};

	union {
		uint8_t minuteInterval = 0;
		uint8_t minHum;
		int16_t minTemp;
	};
};

struct APP_CONFIG {
	CONFIG logConfig;
	CONFIG tempAlertsConfig;
	CONFIG humAlertsConfig;
};

#endif /* INC_APP_CONFIG_H_ */
