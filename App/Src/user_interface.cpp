#include "display_engine.h"
#include "user_interface.h"
#include <cmath>
#include <stdio.h>

static constexpr float NOISE_THRESHOLD = 1;

UserInterface::UserInterface() :
		displayedHum(0),
		displayedTemp(0),
		engine(),
		needsUpdate(true)
{

}

void UserInterface::displayHome() {
	static char buffer[16];

	engine.printHeader("Home");

	// Display temperature
	snprintf(buffer, sizeof(buffer), "%.1fF", displayedTemp);
	engine.printLine(buffer);

	// Display humidity
	snprintf(buffer, sizeof(buffer), "%.1f%%", displayedHum);
	engine.printLine(buffer);

	engine.draw();
}

void UserInterface::update(float temp, float hum) {
	if (weatherChanged(temp, hum)) {
		needsUpdate = true;
		displayedTemp = temp;
		displayedHum = hum;
	}

	if (needsUpdate) {
		displayHome();
		needsUpdate = false;
	}
}

bool UserInterface::weatherChanged(float temp, float hum) const {
	return (
		std::abs(temp - displayedTemp) >= NOISE_THRESHOLD ||
		std::abs(hum - displayedHum) >= NOISE_THRESHOLD
	);
}




