#include "display_engine.h"
#include "user_interface.h"
#include <array>
#include <cmath>
#include <stdio.h>

UserInterface::UserInterface() {
	home();
}

void UserInterface::alertsConfigHelper(int16_t max, int16_t min, char sign, bool isEn) {
	char line1[16];
	char line2[16];
	const char* line3 = isEn ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "Max: %03i%c", max, sign);
	snprintf(line2, sizeof(line2), "Min: %03i%c", min, sign);

	configHelper(line1, line2, line3);
}

void UserInterface::configHelper(const char* l1, const char* l2, const char* l3) {
	engine.setFont(FONT_SIZE::MED);
	engine.printLine(l1, currSelection == 0);
	engine.printLine(l2, currSelection == 1);

	engine.setFont(FONT_SIZE::SMALL);
	engine.printLine(l3, currSelection == 2);
	engine.draw();
}

void UserInterface::home() {
	engine.printHeader("HOME");
	engine.setFont(FONT_SIZE::MED);

	// Display temperature
	snprintf(buffer, sizeof(buffer), "%.1fF", temp);
	engine.printLine(buffer);

	// Display humidity
	snprintf(buffer, sizeof(buffer), "%.1f%%", hum);
	engine.printLine(buffer);

	engine.draw();
}

void UserInterface::logConfig() {
	engine.clear();
	engine.printHeader("LOG CONFIG");

	char line1[16];
	char line2[16];
	const char* line3 = logEnabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "%02uh", logHour);
	snprintf(line2, sizeof(line2), "%02um", logminute);

	configHelper(line1, line2, line3);
}

void UserInterface::menu() {
	std::array<const char*, 4> options {
		"Home",
		"Log Config",
		"Temp Alerts",
		"Humidity Alerts"
	};

	engine.clear();
	engine.printHeader("MENU");
	engine.setFont(FONT_SIZE::SMALL);

	for (uint8_t i = 0; i < options.size(); ++i) {
		engine.printLine(options[i], currSelection == i);
	}

	engine.draw();
}

void UserInterface::humAlertsConfig() {
	engine.clear();
	engine.printHeader("HUM ALERTS");
	alertsConfigHelper(maxHum, minHum, '%', humAlertEnabled);
}

void UserInterface::tempAlertsConfig() {
	engine.clear();
	engine.printHeader("TEMP ALERTS");

	alertsConfigHelper(maxTemp, minTemp, 'F', tempAlertEnabled);
}

void UserInterface::update(float newTemp, float newHum, bool statusOk) {
	if (!statusOk) {
		// display error screen
	}

	temp = newTemp;
	hum = newHum;
}
