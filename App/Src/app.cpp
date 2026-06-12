#include "app.h"
#include "rotary_encoder.h"
#include "sht31_sensor.h"
#include "weather_station.h"

namespace {
	Sht31Sensor sensor;
	WeatherStation ws(sensor);
}

void run_app(I2C_HandleTypeDef* hi2c) {
	// Late bind hardware
	sensor.init(hi2c);
	ws.init();

	while (true) {
		//ws.handleInputs();
		ws.updateComponents();
	}
}
