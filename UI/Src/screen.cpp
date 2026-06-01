#include "screen.h"
#include <stdio.h>

DisplayEngine* Screen::engine = nullptr;

void Screen::init(DisplayEngine* e) {
	engine = e;
}

void Screen::render() {
	engine->clear();
	engine->printHeader(getLabel());
	draw();
	engine->updateScreen();
}

void HomeScreen::draw() const {
	engine->setFont(FONT_SIZE::MED);

	if (weatherData.statusOk) {
		char buffer[16];

		// Display temperature
		snprintf(buffer, sizeof(buffer), "%.1fF", weatherData.temp);
		engine->printLine(buffer);

		// Display humidity
		snprintf(buffer, sizeof(buffer), "%.1f%%", weatherData.hum);
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

UIEvent HomeScreen::handleInput(INPUT_TYPE input) {
	// Any input from the home screen moves to the menu screen
	return LeftHome{};
}

UIEvent MenuScreen::handleInput(INPUT_TYPE input) {
	UIEvent event = NullEvent{};

	switch (input) {
		case INPUT_TYPE::LEFT:
			cursorPos = cursorPos == 0 ? MENU_LENGTH - 1 : cursorPos - 1;
			break;
		case INPUT_TYPE::RIGHT:
			cursorPos = cursorPos == MENU_LENGTH - 1 ? 0 : cursorPos + 1;
			break;
		case INPUT_TYPE::ENTER:
			event = menu[cursorPos];
			cursorPos = 0;
			break;
	}

	return event;
}




