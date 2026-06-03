#include "controller.h"
#include <stm32f4xx_hal.h>
#include <stdio.h>
Controller::Controller(WeatherStation w)
	: ws(w)
	, alertSys(settings.tempAlert, settings.humAlert)
	, logSys(settings.log)
{

}

void Controller::run() {
	constexpr uint32_t UPDATE_INTERVAL = 1000;

	if (HAL_GetTick() - ws.getLastReadTime() >= UPDATE_INTERVAL) {
		ws.update();
		auto weather = ws.read();
		homeScreen.update(weather);
		alertSys.update(weather);
		logSys.update(weather);
	}
	if (uiDirty) {
		currentScreen->render();
		uiDirty = false;
	}
	if (logSys.needsToLog()) {
		logSys.log();
	}

	handleInput();
}

void Controller::init() {
	ws.update();
	auto weather = ws.read();
	homeScreen.update(weather);
	currentScreen->render();
}

void Controller::handleInput() {
	INPUT_TYPE input{};

	if (inputQ.pop(input)) {
		auto newScreen = currentScreen->handleInput(input);

		if (newScreen != currentScreen) {
			currentScreen = newScreen;
		}
		uiDirty = true; // Even if currentScreen is the same, current screen needs to update
	}
}

void Controller::updateLogConfig(uint16_t hour, uint16_t min, bool en) {
	logSys.setConfig({hour, min, en});
}

void Controller::updateTempAlertConfig(uint16_t hour, uint16_t min, bool en) {
	alertSys.setConfig(TempAlertConfig{hour, min, en});
}

void Controller::updateHumAlertConfig(uint16_t hour, uint16_t min, bool en) {
	alertSys.setConfig(HumAlertConfig{hour, min, en});
}

