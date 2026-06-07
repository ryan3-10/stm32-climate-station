#include "screen.h"
#include <stdint.h>
#include <stdio.h>

void ConfigScreen::draw() const {
	char line1[16];
	char line2[16];
	const char* line3 = en ? "Enabled" : "Disabled";

	// construct the lines
	snprintf(line1, sizeof(line1), "%s%02i%c", layout.preData1, d1, layout.postData);
	snprintf(line2, sizeof(line2), "%s%02i%c", layout.preData2, d2, layout.postData);

	// print each line, highlighting the one that cursorPos points to
	engine->setFont(FONT_SIZE::MED);
	engine->printLine(line1, cursorPos == 0);
	engine->printLine(line2, cursorPos == 1);

	engine->setFont(FONT_SIZE::SMALL);
	engine->printLine(line3, cursorPos == 2);
}

Screen* ConfigScreen::handleInput(INPUT_TYPE input) {
	Screen* newScreen = this;

	switch (input) {
		case INPUT_TYPE::LEFT:
			stepDown();
			break;
		case INPUT_TYPE::RIGHT:
			stepUp();
			break;
		case INPUT_TYPE::ENTER:
			cursorPos = cursorPos == NUM_ITEMS - 1 ? 0 : cursorPos + 1;
			break;
	}

	if (cursorPos == 0) {
		newScreen = nextScreen;
		onSave(d1, d2, en);
	}

	return newScreen;
}

void ConfigScreen::stepUp() {
	switch (cursorPos) {
		case 0:
			d1 = d1 == layout.MAX_VALUE ? 0 : d1 + 1;
			break;
		case 1:
			d2 = d2 == layout.MAX_VALUE ? 0 : d2 + 1;
			break;
		case 2:
			en = !en;
			break;
	}
}

void ConfigScreen::stepDown() {
	switch (cursorPos) {
		case 0:
			d1 = d1 == 0 ? layout.MAX_VALUE : d1 - 1;
			break;
		case 1:
			d2 = d2 == 0 ? layout.MAX_VALUE : d2 - 1;
			break;
		case 2:
			en = !en;
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
