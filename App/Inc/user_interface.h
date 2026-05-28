#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

#include "display_engine.h"

class UserInterface {
private:
	bool displayedLogEnabled;
	bool needsUpdate;

	char buffer[16];

	DisplayEngine engine;

	float displayedHum;
	float displayedTemp;

	uint8_t currSelection;
	uint8_t displayedLogMin;
	uint8_t displayedLogHour;

	void displayHome();
	void displayLogConfig();
	void displayMenu();
	bool weatherChanged(float temp, float hum) const;

public:
	UserInterface();
	UserInterface(const UserInterface&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;
	UserInterface(UserInterface&&) = delete;
	UserInterface& operator=(UserInterface&&) = delete;
};


#endif /* INC_USER_INTERFACE_H_ */
