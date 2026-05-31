#include "app.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherStation ws(sensor);
	Controller c(ws);
	c.init();
	c.run();
}
