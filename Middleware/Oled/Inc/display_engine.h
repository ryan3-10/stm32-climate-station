#ifndef OLED_INC_DISPLAY_ENGINE_H_
#define OLED_INC_DISPLAY_ENGINE_H_

#include "fonts.h"
#include <stdint.h>

enum class FONT_SIZE : uint8_t {
	SMALL,
	MED,
	LARGE
};

class DisplayEngine {
private:
	FontDef_t font;
	uint8_t row;

	uint8_t getPadding(const char* buffer) const;
	void setPos(uint8_t x, uint8_t y) const;

public:
	DisplayEngine();

	void clear() const;
	void draw() const;
	void jumpToBodyStart();
	void newLine();
	void print(const char* buffer, bool highlight=false) const;
	void printHeader(const char* buffer);
	void printLine(const char* str, bool highlight=false);
	void setFont(const FONT_SIZE fontSize);
};



#endif /* OLED_INC_DISPLAY_ENGINE_H_ */
