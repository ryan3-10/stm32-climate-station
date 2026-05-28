#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

#include "display_engine.h"

class UserInterface {
private:
	bool humAlertEnabled	= false;
	bool logEnabled			= false;
	bool tempAlertEnabled 	= false;
	bool needsUpdate 		= false;

	char buffer[16];

	DisplayEngine engine;

	float hum	= 0.0f;
	float temp	= 0.0f;

	uint8_t currSelection	= 0;
	uint8_t logminute		= 0;
	uint8_t logHour			= 0;

	int8_t maxHum	= 0;
	int8_t minHum	= 0;

	int16_t maxTemp	= 0;
	int16_t minTemp	= 0;

	void alertsConfigHelper(int16_t max, int16_t min, char sign, bool isEnabled);
	void configHelper(const char* l1, const char* l2, const char* l3);
	void home();
	void logConfig();
	void menu();
	void humAlertsConfig();
	void tempAlertsConfig();

public:
	UserInterface();
};


#endif /* INC_USER_INTERFACE_H_ */
