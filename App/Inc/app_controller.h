#ifndef APP_CONTROLLER_H_
#define APP_CONTROLLER_H_

#include "app_config.h"
#include "user_interface.h"
#include "weather_station.h"
#include <stm32f4xx_hal.h>

class AppController {
public:
	AppController(I2C_HandleTypeDef* hi2c);
	void run();

private:
	APP_CONFIG config;
	Sht31Sensor sensor;
	WeatherStation ws;
	UserInterface ui;
};

#endif /* APP_CONTROLLER_H_ */
