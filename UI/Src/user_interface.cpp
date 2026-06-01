#include "screen.h"
#include "settings.h"
#include "user_interface.h"

namespace {
	ConfigScreenLayout logLayout = {
		.header 		= "Log Config",
		.MAX_VALUE 		= 99,
		.MIN_DATA_WIDTH = 2,
		.preData1 		= "Hr:",
		.preData2 		= "Min:",
		.postData 		= ' ',
		.onSave			= EVENT_TYPE::LOG_CONFIG_SAVE
	};

	ConfigScreenLayout tempAlertsLayout = {
		.header 		= "Temp Alerts",
		.MAX_VALUE 		= 200,
		.MIN_DATA_WIDTH	= 3,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= 'F',
		.onSave			= EVENT_TYPE::TEMP_CONFIG_SAVE
	};

	ConfigScreenLayout humAlertsLayout = {
		.header 		= "Hum Alerts",
		.MAX_VALUE 		= 100,
		.MIN_DATA_WIDTH = 3,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= '%',
		.onSave 		= EVENT_TYPE::HUM_CONFIG_SAVE
	};
}

UserInterface::UserInterface(const SettingsConfig& settings)
	: logC(settings.getLogData())
	, tempC(settings.getTempAlertData())
	, humC(settings.getHumAlertData())
	, logScreen(logC, logLayout)
	, tempAlertsScreen(tempC, tempAlertsLayout)
	, humAlertsScreen(humC, humAlertsLayout)
	, menuScreen(menuItems)
	, currentScreen(homeScreen)
{
	Screen::init();
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
