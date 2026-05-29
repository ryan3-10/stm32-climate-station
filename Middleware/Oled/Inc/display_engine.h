#ifndef OLED_INC_DISPLAY_ENGINE_H_
#define OLED_INC_DISPLAY_ENGINE_H_

#include "fonts.h"
#include "ssd1306.h"
#include <stdint.h>

enum class FONT_SIZE : uint8_t {
	SMALL,
	MED,
	LARGE
};

class DisplayEngine {
public:
	DisplayEngine() { SSD1306_Init(); }
	void clear() const;
	void draw() const;
	void jumpToBodyStart();
	void newLine();
	void print(const char* buffer, bool highlight=false) const;
	void printHeader(const char* buffer);
	void printLine(const char* str, bool highlight=false);
	void setFont(const FONT_SIZE fontSize);

private:
	uint8_t getPadding(const char* buffer) const;
	void setPos(uint8_t x, uint8_t y) const;

	FontDef_t font = Font_11x18;
	uint8_t row = 0;
};



#endif /* OLED_INC_DISPLAY_ENGINE_H_ */
