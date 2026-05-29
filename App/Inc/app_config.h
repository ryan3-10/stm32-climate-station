#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <stdint.h>

struct APP_CONFIG {
	struct LOG_CONFIG {
		bool enabled = false;
		uint8_t hourInterval = 0;
		uint8_t minuteInterval = 0;
	};

	struct ALERT_CONFIG {
		bool humAlertsEnabled = false;
		bool tempAlertsEnabled = false;
		int16_t maxTemp = 0;
		int16_t minTemp = 0;
		uint8_t maxHum = 0;
		uint8_t minHum = 0;
	};
};

#endif /* INC_APP_CONFIG_H_ */
