#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct APP_CONFIG {
	struct LOG_CONFIG {
		bool enabled;
		uint8_t hourInterval;
		uint8_t minuteInterval;
	};

	struct ALERT_CONFIG {
		bool humAlertsEnabled;
		bool tempAlertsEnabled;
		int16_t maxTemp;
		int16_t minTemp;
		uint8_t maxHum;
		uint8_t minHum;
	};
};

#endif /* INC_APP_CONFIG_H_ */
