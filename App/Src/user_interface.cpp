#include "display_engine.h"
#include "user_interface.h"
#include <array>
#include <cmath>
#include <stdio.h>

static constexpr float NOISE_THRESHOLD = 1;

UserInterface::UserInterface() :
	displayedLogEnabled(false),
	needsUpdate(true),
	engine(),
	displayedHum(0),
	displayedTemp(0),
	currSelection(0),
	displayedLogMin(0),
	displayedLogHour(0)
{
	displayHome();
}

void UserInterface::displayHome() {
	engine.printHeader("HOME");
	engine.setFont(FONT_SIZE::MED);

	// Display temperature
	snprintf(buffer, sizeof(buffer), "%.1fF", displayedTemp);
	engine.printLine(buffer);

	// Display humidity
	snprintf(buffer, sizeof(buffer), "%.1f%%", displayedHum);
	engine.printLine(buffer);

	engine.draw();
}

void UserInterface::displayLogConfig() {
	engine.clear();
	engine.printHeader("LOG CONFIG");
	engine.setFont(FONT_SIZE::MED);

	snprintf(buffer, sizeof(buffer), "%02uh", displayedLogHour);
	engine.printLine(buffer, currSelection == 0);

	snprintf(buffer, sizeof(buffer), "%02um", displayedLogMin);
	engine.printLine(buffer, currSelection == 1);

	engine.setFont(FONT_SIZE::SMALL);
	engine.printLine(displayedLogEnabled ? "Enabled" : "Disabled", currSelection == 2);
	engine.draw();
}

void UserInterface::displayMenu() {
	static std::array<const char*, 3> options { "Home", "Log Config", "Alert Config" };

	engine.clear();
	engine.printHeader("MENU");
	engine.setFont(FONT_SIZE::SMALL);

	for (uint8_t i = 0; i < options.size(); ++i) {
		engine.printLine(options[i], currSelection == i);
	}

	engine.draw();
}

bool UserInterface::weatherChanged(float temp, float hum) const {
	return (
		std::abs(temp - displayedTemp) >= NOISE_THRESHOLD ||
		std::abs(hum - displayedHum) >= NOISE_THRESHOLD
	);
}




