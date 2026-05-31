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

