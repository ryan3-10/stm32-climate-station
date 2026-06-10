#include "screen.h"
#include <stdio.h>

void Screen::init() {
	static DisplayEngine e;
	engine = &e;
}

void Screen::render() {
	engine->clear();
	engine->printHeader(getLabel());
	draw();
	engine->updateScreen();
}

void HomeScreen::draw() const {
	engine->setFont(FONT_SIZE::MED);

	if (weather.statusOk) {
		char buffer[16];

		// Display temperature
		snprintf(buffer, sizeof(buffer), "%.1fF", weather.temp);
		engine->printLine(buffer);

		// Display humidity
		snprintf(buffer, sizeof(buffer), "%.1f%%", weather.hum);
		engine->printLine(buffer);
	}
	else { // If sensor is in error state, print error message
		engine->printLine("SENSOR");
		engine->printLine("ERROR");
	}
}

void MenuScreen::draw() const {
	engine->setFont(FONT_SIZE::SMALL);

	// Print each menu item, highlighting the one that cursor index points to
	for (uint8_t i = 0; i < menu.size(); ++i) {
		engine->printLine(menu[i]->getLabel(), cursorPos == i);
	}
}

Screen* HomeScreen::handleInput(INPUT_TYPE input) {
	// Any input from the home screen moves to the menu screen
	return nextScreen;
}

Screen* MenuScreen::handleInput(INPUT_TYPE input) {
	Screen* newScreen = this;

	switch (input) {
		case INPUT_TYPE::LEFT:
			cursorPos = cursorPos == 0 ? MENU_LENGTH - 1 : cursorPos - 1;
			break;
		case INPUT_TYPE::RIGHT:
			cursorPos = cursorPos == MENU_LENGTH - 1 ? 0 : cursorPos + 1;
			break;
		case INPUT_TYPE::ENTER:
			newScreen = menu[cursorPos];
			cursorPos = 0;
			break;
	}

	return newScreen;
}




