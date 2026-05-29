#include "app.h"
#include "app_controller.h"
#include "ssd1306.h"
#include "user_interface.h"
#include "weather_station.h"

void run_app(I2C_HandleTypeDef* hi2c) {
	AppController appController(hi2c);
	appController.run();
}
