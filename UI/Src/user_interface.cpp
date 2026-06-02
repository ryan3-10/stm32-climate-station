#include "screen.h"
#include "settings.h"
#include "user_interface.h"

ConfigScreenLayout logLayout = {
		.header 		= "Log Config",
		.MAX_VALUE 		= 99,
		.preData1 		= "Hr:",
		.preData2 		= "Min:",
		.postData 		= ' ',
		.onSave			= EVENT_TYPE::LOG_CONFIG_SAVE
	};

	ConfigScreenLayout tempAlertsLayout = {
		.header 		= "Temp Alerts",
		.MAX_VALUE 		= 200,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= 'F',
		.onSave			= EVENT_TYPE::TEMP_CONFIG_SAVE
	};

	ConfigScreenLayout humAlertsLayout = {
		.header 		= "Hum Alerts",
		.MAX_VALUE 		= 100,
		.preData1 		= "Max: ",
		.preData2 		= "Min: ",
		.postData 		= '%',
		.onSave 		= EVENT_TYPE::HUM_CONFIG_SAVE
	};

UserInterface::UserInterface(
	const LogConfig& logC,
	const TempAlertConfig& tAlertC,
	const HumAlertConfig& hAlertC
)	: logScreen(logLayout)
	, tempAlertsScreen(tempAlertsLayout)
	, humAlertsScreen(humAlertsLayout)
{
	Screen::init();

	logScreen.setEdits(logC.hourInt, logC.minInt, logC.enabled);
	tempAlertsScreen.setEdits(tAlertC.maxTemp, tAlertC.minTemp, tAlertC.enabled);
	humAlertsScreen.setEdits(hAlertC.maxHum, hAlertC.minHum, hAlertC.enabled);
}

void UserInterface::render() {
	currentScreen->render();
	isDirty = false;
}

void UserInterface::update(const WeatherData& data) {
	homeScreen.update(data.temp, data.hum, data.statusOk);

	if (currentScreen == &homeScreen) {
		isDirty = true;
	}
}
EVENT_TYPE UserInterface::handlInput(INPUT_TYPE input) {
	isDirty = true;
	return currentScreen->handleInput(input);
}
