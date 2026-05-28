#ifndef OLED_INC_DISPLAY_ENGINE_H_
#define OLED_INC_DISPLAY_ENGINE_H_

#include "fonts.h"
#include <stdint.h>

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
	void print(const char* buffer) const;
	void printHeader(const char* buffer);
	void printLine(const char* str);
};



#endif /* OLED_INC_DISPLAY_ENGINE_H_ */
