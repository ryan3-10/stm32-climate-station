#include "controller.h"
#include <stm32f4xx_hal.h>

Controller::Controller(WeatherStation w)
	: ws(w)
	, alertSys(settings.tempAlert, settings.humAlert)
	, logSys(settings.log)
	, ui(settings.log, settings.tempAlert, settings.humAlert)
{

}

void Controller::run() {
	constexpr uint32_t UPDATE_INTERVAL = 1000;

	if (HAL_GetTick() - ws.getLastReadTime() >= UPDATE_INTERVAL) {
		ws.update();
		auto weather = ws.read();
		ui.update(weather);
		alertSys.update(weather);
	}

	if (ui.needsRender()) {
		ui.render();
	}

	handleInputs();
}

void Controller::init() {
	ws.update();
	auto weather = ws.read();
	ui.update(weather);
	ui.render();
}

void Controller::handleInputs() {
	INPUT_TYPE input;
	EVENT_TYPE event;

	while (inputQ.pop(input)) {
		event = ui.handlInput(input);

		switch (event) {
		case EVENT_TYPE::NULL_EVENT:
			break;
		case EVENT_TYPE::LEFT_HOME:
			ui.toMenu();
			break;
		case EVENT_TYPE::MENU_SELECT:
			ui.toSelected();
			break;
		case EVENT_TYPE::LOG_CONFIG_SAVE:
			// update log system
			ui.toHome();
			break;
		case EVENT_TYPE::TEMP_CONFIG_SAVE:
			// update alert system
			ui.toHome();
			break;
		case EVENT_TYPE::HUM_CONFIG_SAVE:
			// update alert system
			ui.toHome();
			break;
		}
	}
}
