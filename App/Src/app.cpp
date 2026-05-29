#include "app.h"
#include "ssd1306.h"
#include "weather_data.h"
#include "user_interface.h"

namespace {
	constexpr uint32_t UPDATE_INTERVAL = 1000;
}
void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	UserInterface ui;
	WeatherData wd(sensor);
	wd.update();

	while (true) {
		if (HAL_GetTick() - wd.getLastUpdate() >= UPDATE_INTERVAL) {
			wd.update();
		}
	}
}
