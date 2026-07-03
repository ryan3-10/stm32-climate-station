#ifndef MODELS_UI_MODELS_H_
#define MODELS_UI_MODELS_H_

#include "config_models.h"
#include <stdint.h>

enum class INPUT_TYPE : uint8_t {
	LEFT,
	ENTER,
	RIGHT
};

enum class EVENT_TYPE : uint8_t {
	NONE,
	HOME_LEFT,
	MENU_ITEM_SELECTED,
	LOG_CONFIG_SAVED,
	TEMP_CONFIG_SAVED,
	HUM_CONFIG_SAVED
};

struct ConfigScreenLayout {
	const char* header;
	uint16_t MAX_VALUE;
	const char* preData1;
	const char* preData2;
	const char postData;
};

struct ConfigEdit {
	uint16_t d1 = 0;
	uint16_t d2 = 0;
	bool en = false;
};

enum class SubmissionType : uint8_t {
	Log,
	Temp,
	Hum
};

struct Submission {
	SubmissionType type;
	ConfigEdit config;
};

#endif /* MODELS_UI_MODELS_H_ */
