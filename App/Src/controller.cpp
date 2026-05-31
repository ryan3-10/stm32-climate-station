#include "controller.h"

Controller::Controller(WeatherStation w) :
	ws(w),
	ui(settings)
{

}

void Controller::run() {
	constexpr uint32_t UPDATE_INTERVAL = 1000;

	if (HAL_GetTick() - ws.getLastReadTime() >= UPDATE_INTERVAL) {
		ws.update();
	}

	if (ui.needsRender()) {
		ui.render();
	}
}

void Controller::init() {
	ws.addObserver(&ui);
	ws.update();
	ui.render();
}
