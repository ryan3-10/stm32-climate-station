#include "sht31_sensor.h"
#include "ssd1306.h"
#include "user_interface.h"
#include <cmath>
#include <stdio.h>

static constexpr float noiseThreshold = 1;

UserInterface::UserInterface() : displayedHum(0), displayedTemp(0), needsUpdate(true) {

}

void UserInterface::displayHome() const {
	char buffer[8];

	// Display temperature
	sprintf(buffer, "%.1f", displayedTemp);
	SSD1306_GotoXY (10, 15);
	SSD1306_Puts (buffer, &Font_11x18, SSD1306_NOT_HIGHLIGHTED);
	SSD1306_DrawCircle(75, 18, 2, SSD1306_NOT_HIGHLIGHTED);
	SSD1306_GotoXY (80, 16);
	SSD1306_Puts ("F", &Font_7x10, SSD1306_NOT_HIGHLIGHTED);

	// Display humidity
	sprintf(buffer, "%.1f", displayedHum);
	SSD1306_GotoXY (10, 35);
	SSD1306_Puts (buffer, &Font_11x18, SSD1306_NOT_HIGHLIGHTED);
	SSD1306_GotoXY (72, 35);
	SSD1306_Puts ("%", &Font_7x10, SSD1306_NOT_HIGHLIGHTED);
	SSD1306_UpdateScreen();
}

void UserInterface::update(float temp, float hum) {
	if (weatherChanged(temp, hum)) {
		needsUpdate = true;
		displayedTemp = temp;
		displayedHum = hum;
	}

	if (needsUpdate) {
		displayHome();
		needsUpdate = false;
	}
}

bool UserInterface::weatherChanged(float temp, float hum) const {
	return (
		std::abs(temp - displayedTemp) >= noiseThreshold ||
		std::abs(hum - displayedHum) >= noiseThreshold
	);
}




