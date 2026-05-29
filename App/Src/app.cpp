#include <weather_station.h>
#include "app.h"
#include "ssd1306.h"
#include "user_interface.h"

namespace {
	constexpr uint32_t UPDATE_INTERVAL = 1000;
}
void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);

	UserInterface ui;

	WeatherStation ws(sensor);
	ws.subscribe(&ui);
	ws.update();

	while (true) {
		if (HAL_GetTick() - ws.getLastUpdate() >= UPDATE_INTERVAL) {
			ws.update();
		}
	}
}
