#include "weather_station.h"
#include <stm32f4xx_hal.h>
#include <stdio.h>
WeatherStation::WeatherStation(Sht31Sensor& s)
	: sensor(s)
	, alertSys(settings.tempAlert, settings.humAlert)
	, logSys(settings.log)
{

}

void WeatherStation::updateComponents() {
	constexpr uint32_t UPDATE_INTERVAL = 1000;

	if (HAL_GetTick() - sensor.getLastReadTime() >= UPDATE_INTERVAL) {
		auto weather = sensor.read();
		homeScreen.update(weather);
		alertSys.update(weather);
		logSys.update(weather);

		if (currentScreen == &homeScreen) {
			uiDirty = true;
		}
	}
	if (uiDirty) {
		currentScreen->render();
		uiDirty = false;
	}
	if (logSys.needsToLog()) {
		logSys.log();
	}
}

void WeatherStation::init() {
	Screen::init();
	auto weather = sensor.read();
	homeScreen.update(weather);
	currentScreen->render();
}

void WeatherStation::handleInput(INPUT_TYPE input) {
	currentScreen = currentScreen->handleInput(input);
	uiDirty = true; // Even if currentScreen is the same, current screen needs to update
}

void WeatherStation::updateLogConfig(uint16_t hour, uint16_t min, bool en) {
	logSys.setConfig({hour, min, en});
}

void WeatherStation::updateTempAlertConfig(uint16_t hour, uint16_t min, bool en) {
	alertSys.setConfig(TempAlertConfig{hour, min, en});
}

void WeatherStation::updateHumAlertConfig(uint16_t hour, uint16_t min, bool en) {
	alertSys.setConfig(HumAlertConfig{hour, min, en});
}

