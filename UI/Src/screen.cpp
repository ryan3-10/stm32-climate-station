#include "screen.h"
#include <stdio.h>

DisplayEngine* Screen::engine = nullptr;

void Screen::init() {
	static DisplayEngine eng;
	engine = &eng;
}

void Screen::render(bool freshRender) {
	if (freshRender) {
		engine->clear();
		engine->printHeader(getHeader());
		//cleanState();
	}

	engine->jumpToBodyStart();
	renderHelper();
}

void HomeScreen::renderHelper() const {
	char buffer[16];

	engine->setFont(FONT_SIZE::MED);

	// If sensor is in error state, print error message
	if (!weatherData.statusOk) {
		engine->printLine("SENSOR");
		engine->printLine("ERROR");
	}

	else {
		// Display temperature
		snprintf(buffer, sizeof(buffer), "%.1fF", weatherData.temperature);
		engine->printLine(buffer);

		// Display humidity
		snprintf(buffer, sizeof(buffer), "%.1f%%", weatherData.humidity);
		engine->printLine(buffer);
	}

	engine->draw();
}

void MenuScreen::renderHelper() const {
	engine->setFont(FONT_SIZE::SMALL);

	// Print each menu item, highlighting the one that cursor index points to
	for (uint8_t i = 0; i < menu.size(); ++i) {
		engine->printLine(menu[i]->getLabel(), cursorPos == i);
	}

	engine->draw();
}

