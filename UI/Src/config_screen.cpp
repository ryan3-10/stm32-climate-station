#include "config_screen.h"
#include <stdio.h>

void ConfigScreen::configHelper(const char* l1, const char* l2, const char* l3) const {
	engine.setFont(FONT_SIZE::MED);
	engine.printLine(l1, cursorPos == 0);
	engine.printLine(l2, cursorPos == 1);

	engine.setFont(FONT_SIZE::SMALL);
	engine.printLine(l3, cursorPos == 2);
	engine.draw();
}

void AlertsConfigScreen::alertsConfigHelper(uint16_t max, uint16_t min, char sign) const {
	char line1[16];
	char line2[16];
	const char* line3 = editConfig.enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "Max: %03i%c", max, sign);
	snprintf(line2, sizeof(line2), "Min: %03i%c", min, sign);

	configHelper(line1, line2, line3);
}

void ConfigScreen::cleanState() {
	editConfig = masterConfig;
	cursorPos = 0;
}

void LogConfigScreen::renderHelper() const {
	char line1[16];
	char line2[16];
	const char* line3 = editConfig.enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "%02uh", editConfig.hourInterval);
	snprintf(line2, sizeof(line2), "%02um", editConfig.minuteInterval);

	configHelper(line1, line2, line3);
}

void TempAlertsConfigScreen::renderHelper() const {
	alertsConfigHelper(editConfig.maxTemp, editConfig.minTemp, 'F');
}

void HumAlertsConfigScreen::renderHelper() const {
	alertsConfigHelper(editConfig.maxHum, editConfig.minHum, '%');
}




