#include "app_controller.h"

namespace {
	constexpr uint32_t UPDATE_INTERVAL = 1000;
}

AppController::AppController(I2C_HandleTypeDef* hi2c) :
	sensor(hi2c),
	ws(sensor),
	ui(config, ws.getLiveData())
{

}

void AppController::run() {
	ws.subscribe(&ui);
	ws.update();
	ui.enable();

	while (true) {
		if (HAL_GetTick() - ws.getLastUpdate() >= UPDATE_INTERVAL) {
			ws.update();
		}
	}
}



