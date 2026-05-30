#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct CONFIG {
	bool enabled = false;

	union {
		int16_t maxTemp = 0;
		uint8_t hourInterval;
		uint8_t maxHum;
	};

	union {
		int16_t minTemp = 0;
		uint8_t minuteInterval;
		uint8_t minHum;
	};
};

struct APP_CONFIG {
	CONFIG logConfig;
	CONFIG tempAlertsConfig;
	CONFIG humAlertsConfig;
};

#endif /* INC_APP_CONFIG_H_ */
