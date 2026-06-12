#ifndef APP_WEATHER_STATION_H_
#define APP_WEATHER_STATION_H_

#include <settings_manager.h>
#include "rotary_encoder.h"
#include "screen.h"
#include "sht31_sensor.h"
#include "system.h"
#include <stdint.h>

class WeatherStation {
public:
	WeatherStation(Sht31Sensor& s);
	void init();
	void updateComponents();


private:
	void updateLogConfig(uint16_t hour, uint16_t min, bool en);
	void updateTempAlertConfig(uint16_t max, uint16_t min, bool en);
	void updateHumAlertConfig(uint16_t max, uint16_t min, bool en);


	Settings settings;
	Sht31Sensor& sensor;
	AlertSystem alertSys;
	LogSystem logSys;


};


#endif /* APP_CONTROLLER_H_ */
