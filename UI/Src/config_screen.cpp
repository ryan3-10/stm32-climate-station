#include "display_engine.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>

void configHelper(
	DisplayEngine* engine,
	const char* l1,
	const char* l2,
	const char* l3,
	uint8_t cursorPos
) {
	engine->setFont(FONT_SIZE::MED);
	engine->printLine(l1, cursorPos == 0);
	engine->printLine(l2, cursorPos == 1);

	engine->setFont(FONT_SIZE::SMALL);
	engine->printLine(l3, cursorPos == 2);
}

void alertsHelper(
	DisplayEngine* engine,
	bool enabled,
	uint16_t max,
	uint16_t min,
	char sign,
	uint8_t cursorPos
) {
	char line1[16];
	char line2[16];
	const char* line3 = enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "Max: %03i%c", max, sign);
	snprintf(line2, sizeof(line2), "Min: %03i%c", min, sign);

	configHelper(engine, line1, line2, line3, cursorPos);
}

void LogConfigScreen::draw() const {
	char line1[16];
	char line2[16];
	const char* line3 = logData.enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "%02uh", logData.hourInt);
	snprintf(line2, sizeof(line2), "%02um", logData.minInt);

	configHelper(engine, line1, line2, line3, cursorPos);
}

void TempAlertsScreen::draw() const {
	alertsHelper(
		engine,
		alertData.tempEnabled,
		alertData.maxTemp,
		alertData.minTemp,
		'%',
		cursorPos
	);
}

void HumAlertsScreen::draw() const {
	alertsHelper(
		engine,
		alertData.humEnabled,
		alertData.maxHum,
		alertData.minHum,
		'%',
		cursorPos
	);
}
