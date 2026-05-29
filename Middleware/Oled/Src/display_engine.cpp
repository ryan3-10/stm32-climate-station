#include "display_engine.h"
#include "fonts.h"
#include "ssd1306.h"
#include <stdint.h>
#include <stdio.h>

constexpr uint8_t BODY_START_ROW = 16;

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

void DisplayEngine::print(const char* buffer, bool highlight) const {
	SSD1306_Puts(
		buffer,
		&font,
		highlight ? SSD1306_HIGHLIGHTED : SSD1306_NOT_HIGHLIGHTED
	);
}

void DisplayEngine::printHeader(const char* buffer) {
	setFont(FONT_SIZE::MED);
	row = 0;
	printLine(buffer);
	jumpToBodyStart();
}

void DisplayEngine::printLine(const char* buffer, bool highlight) {
	uint8_t padding = getPadding(buffer);
	setPos(padding, row);
	print(buffer, highlight);
	newLine();
}

void DisplayEngine::setFont(const FONT_SIZE fontSize) {
	switch (fontSize) {
		case FONT_SIZE::SMALL:
			font = Font_7x10;
			break;
		case FONT_SIZE::MED:
			font = Font_11x18;
			break;
		case FONT_SIZE::LARGE:
			font = Font_16x26;
			break;
	}
}

void DisplayEngine::setPos(uint8_t x, uint8_t y) const {
	SSD1306_GotoXY(x, y);
}







