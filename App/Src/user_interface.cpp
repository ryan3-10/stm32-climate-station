#include "display_engine.h"
#include "user_interface.h"
#include <array>
#include <cmath>
#include <stdio.h>

static constexpr float NOISE_THRESHOLD = 1;

UserInterface::UserInterface() :
		currSelection(00),
		displayedHum(0),
		displayedTemp(0),
		engine(),
		needsUpdate(true)
{

}

void UserInterface::displayHome() {
	engine.printHeader("Home");
	engine.setFont(FONT_SIZE::MED);

	// Display temperature
	snprintf(buffer, sizeof(buffer), "%.1fF", displayedTemp);
	engine.printLine(buffer);

	// Display humidity
	snprintf(buffer, sizeof(buffer), "%.1f%%", displayedHum);
	engine.printLine(buffer);

	engine.draw();
}

void UserInterface::displayMenu() {
	static std::array<const char*, 3> options { "Home", "Log Config", "Alert Config" };

	engine.clear();
	engine.printHeader("Menu");
	engine.setFont(FONT_SIZE::SMALL);

	for (uint8_t i = 0; i < options.size(); ++i) {
		engine.printLine(options[i], currSelection == i);
	}

	engine.draw();
}

void UserInterface::update(float temp, float hum) {
	if (weatherChanged(temp, hum)) {
		needsUpdate = true;
		displayedTemp = temp;
		displayedHum = hum;
	}

	if (needsUpdate) {
		displayMenu();
		needsUpdate = false;
	}
}

bool UserInterface::weatherChanged(float temp, float hum) const {
	return (
		std::abs(temp - displayedTemp) >= NOISE_THRESHOLD ||
		std::abs(hum - displayedHum) >= NOISE_THRESHOLD
	);
}




