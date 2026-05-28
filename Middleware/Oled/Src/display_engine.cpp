#include "display_engine.h"
#include "fonts.h"
#include "ssd1306.h"
#include <stdint.h>
#include <stdio.h>

constexpr uint8_t BODY_START_ROW = 15;

DisplayEngine::DisplayEngine() : font(Font_11x18), row(0) {

}

void DisplayEngine::clear() const {
	SSD1306_Clear();
}

void DisplayEngine::draw() const {
	SSD1306_UpdateScreen();
}

uint8_t DisplayEngine::getPadding(const char* buffer) const {
	FONTS_SIZE_t dimensions;
	FONTS_GetStringSize(buffer, &dimensions, &font);
	return (SSD1306_WIDTH - dimensions.Length) / 2;
}

void DisplayEngine::jumpToBodyStart() {
	row = BODY_START_ROW;
}

void DisplayEngine::newLine() {
	row += font.FontHeight;
}

void DisplayEngine::print(const char* buffer) const {
	SSD1306_Puts(buffer, &font, SSD1306_NOT_HIGHLIGHTED);
}

void DisplayEngine::printHeader(const char* buffer) {
	row = 0;
	printLine(buffer);
	jumpToBodyStart();
}

void DisplayEngine::printLine(const char* buffer) {
	uint8_t padding = getPadding(buffer);
	setPos(padding, row);
	print(buffer);
	newLine();
}

void DisplayEngine::setPos(uint8_t x, uint8_t y) const {
	SSD1306_GotoXY(x, y);
}







