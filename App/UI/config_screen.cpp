#include "config_screen.h"
#include <stdint.h>
#include <stdio.h>

void ConfigScreen::drawBody(DisplayEngine& engine) const {
	char line1[16];
	char line2[16];
	const char* line3 = config.en ? "Enabled" : "Disabled";

	// construct the lines
	snprintf(line1, sizeof(line1), "%s%02i%c", layout.preData1, config.d1, layout.postData);
	snprintf(line2, sizeof(line2), "%s%02i%c", layout.preData2, config.d2, layout.postData);

	// print each line, highlighting the one that cursorPos points to
	engine.setFont(FONT_SIZE::MED);
	engine.printLine(line1, cursorPos == 0);
	engine.printLine(line2, cursorPos == 1);

	engine.setFont(FONT_SIZE::SMALL);
	engine.printLine(line3, cursorPos == 2);
}

EVENT_TYPE ConfigScreen::handleInput(INPUT_TYPE input) {
	EVENT_TYPE event = EVENT_TYPE::NONE;
	switch (input) {
		case INPUT_TYPE::LEFT:
			stepDown();
			break;
		case INPUT_TYPE::RIGHT:
			stepUp();
			break;
		case INPUT_TYPE::ENTER:
			++cursorPos;
			break;
	}

	if (cursorPos >= NUM_ITEMS) {
		cursorPos = 0;
		event = onSave;
	}

	return event;
}

void ConfigScreen::stepUp() {
	switch (cursorPos) {
		case 0:
			config.d1 = config.d1 == layout.MAX_VALUE ? 0 : config.d1 + 1;
			break;
		case 1:
			config.d2 = config.d2 == layout.MAX_VALUE ? 0 : config.d2 + 1;
			break;
		case 2:
			config.en = !config.en;
			break;
	}
}

void ConfigScreen::stepDown() {
	switch (cursorPos) {
		case 0:
			config.d1 = config.d1 == 0 ? layout.MAX_VALUE : config.d1 - 1;
			break;
		case 1:
			config.d2 = config.d2 == 0 ? layout.MAX_VALUE : config.d2 - 1;
			break;
		case 2:
			config.en = !config.en;
			break;
	}
}

ConfigScreenLayout LogLayout() {
	return ConfigScreenLayout {
		.header 		= "Log Config",
		.MAX_VALUE 		= 99,
		.preData1 		= "Hr:",
		.preData2 		= "Min:",
		.postData 		= ' '
	};
}

ConfigScreenLayout TempAlertLayout() {
	return ConfigScreenLayout {
		.header 		= "Temp Alerts",
		.MAX_VALUE 		= 200,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= 'F'
	};
}

ConfigScreenLayout HumAlertLayout() {
	return ConfigScreenLayout {
		.header 		= "Hum Alerts",
		.MAX_VALUE 		= 100,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= '%'
	};
}
