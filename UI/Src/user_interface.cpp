#include "screen.h"
#include "user_interface.h"
#include "weather_station.h"
#include <array>

UserInterface::UserInterface(const APP_CONFIG& ac, const WeatherData& wd)
	:
	appConfig(ac),
	weatherData(wd),
	homeScreen(weatherData),
	logScreen(appConfig.logConfig),
	tempAlertsScreen(appConfig.tempAlertsConfig),
	humAlertsScreen(appConfig.humAlertsConfig),
	menuScreen(menuItems),
	currentScreen(homeScreen)
{
	Screen::init();
}

void UserInterface::enable() {
	enabled = true;
	currentScreen.render(true);
}

void UserInterface::update() {
	if (enabled && &currentScreen == &homeScreen) {
		currentScreen.render(false);
	}
}
