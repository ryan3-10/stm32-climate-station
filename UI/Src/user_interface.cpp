#include "settings.h"
#include "user_interface.h"

UserInterface::UserInterface(const SettingsConfig& settings)
	:
	logScreen(settings.getLogData()),
	tempAlertsScreen(settings.getAlertData()),
	humAlertsScreen(settings.getAlertData()),
	menuScreen(menuItems),
	currentScreen(homeScreen)
{
	Screen::init(&engine);
}

void UserInterface::render() {
	currentScreen.render();
	isDirty = false;
}

void UserInterface::update(const WeatherData& data) {
	homeScreen.update(data);

	if (&currentScreen == &homeScreen) {
		isDirty = true;
	}
}
