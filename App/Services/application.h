#ifndef SERVICES_APPLICATION_H_
#define SERVICES_APPLICATION_H_

#include "alert_system.h"
#include "ds3231_clock.h"
#include "ds3231.h"
#include "file_manager.h"
#include "logger.h"
#include "passive_buzzer.h"
#include "rotary_encoder.h"
#include "sht31.h"
#include "sht31_sensor.h"
#include "system_health.h"
#include "ui_manager.h"
#include "weather_station.h"

class Application {
public:
	void run();
	void init(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer);

private:
	void handleSubmission(Submission sub);
	void handleInputs();
	Sht31 sht31;
	Sht31Sensor sensor{sht31};
	WeatherStation ws{sensor};
	Ds3231 ds3231;
	Ds3231Clock clock{ds3231};
	FileManager fileManager;
	Logger<FileManager> logger{clock, fileManager};
	PassiveBuzzer buzzer;
	AlertSystem alertSystem{buzzer};
	UIManager ui;
	RotaryEncoder rotEncoder;
	SystemHealth systemHealth{{&sensor, &clock, &fileManager}};
};

#endif /* SERVICES_APPLICATION_H_ */
