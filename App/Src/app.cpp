#include <app.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>
#include <weather_data.h>
#include "../../Middleware/Inc/sht31_sensor.h"

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherData wd(sensor);

	while (true) {
		printf("Temp: %i Hum: %i\n", (int)wd.getTemperature(), (int)wd.getHumidity());
		wd.update();
	}
}




