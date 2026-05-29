#include "app.h"
#include "ssd1306.h"
#include "weather_data.h"
#include "user_interface.h"

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	UserInterface ui;
	WeatherData wd(sensor);

	while (true) {
		wd.update();
	}
}
