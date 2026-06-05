#include "app.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include <stdio.h>

Controller* cPtr = nullptr;

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherStation ws(sensor);
	Controller c(ws);
	cPtr = &c;
	c.init();

	while (true) {
		c.run();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	printf("%u\n", GPIO_Pin);
}
