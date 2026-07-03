#ifndef MODELS_CONFIG_MODELS_H_
#define MODELS_CONFIG_MODELS_H_

#include <stdint.h>

struct LogConfig {
	uint16_t hourInt = 0;
	uint16_t minInt = 0;
	bool enabled = false;

	bool operator==(const LogConfig& oth) const {
		return hourInt == oth.hourInt && minInt == oth.minInt && enabled == oth.enabled;
	}

	bool operator!=(const LogConfig& oth) const {
		return !(*this == oth);
	}
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


#endif /* MODELS_CONFIG_MODELS_H_ */
