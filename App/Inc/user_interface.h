#ifndef INC_USER_INTERFACE_H_
#define INC_USER_INTERFACE_H_

#include "display_engine.h"

class UserInterface {
private:
	float displayedHum;
	float displayedTemp;
	DisplayEngine engine;
	bool needsUpdate;

	void displayHome();
	bool weatherChanged(float temp, float hum) const;

public:
	UserInterface();
	UserInterface(const UserInterface&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;
	UserInterface(UserInterface&&) = delete;
	UserInterface& operator=(UserInterface&&) = delete;

	void update(float temp, float hum);
};


#endif /* INC_USER_INTERFACE_H_ */
