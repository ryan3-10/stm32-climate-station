#include "alert_system.h"
#include "app.h"
#include "ds3231_clock.h"
#include "file_manager.h"
#include "logger.h"
#include "passive_buzzer.h"
#include "settings_manager.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include "ui_manager.h"

namespace {
	constexpr uint32_t READ_INTERVAL = 1000;
	Sht31Sensor sensor;
	WeatherStation ws(sensor);
	SettingsManager settingsMan;
	Ds3231Clock clock;
	FileManager fileManager;
	Logger logger(settingsMan.getLogConfig(), clock, fileManager);
	PassiveBuzzer buzzer;
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig(), buzzer);
	UIManager uiManager(settingsMan);
}

void run_app() {
	if (ws.timeSinceLastRead() >= READ_INTERVAL) {
		ws.update();
		ws.notifyObservers();
	}

	if (logger.needsToLog()) {
		logger.log();
	}

	SystemHealth newSysHealth = {
		sensor.getStatus() == SENSOR_STATUS::OK,
		true,
		clock.getStatus() == CLOCK_STATUS::OK
	};

	uiManager.updateHeaderInfo(newSysHealth);
	uiManager.renderIfDirty();
	uiManager.handleInputs();
	alertSystem.update();
}

void init_app(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	// Late bind hardware
	SSD1306_Init();
	sensor.init(hi2c);
	clock.init(hi2c);
	fileManager.init();
	buzzer.init(pvmTimer, TIM_CHANNEL_1);
	buzzer.setPattern(standardPattern2);

	// Weather observers
	ws.addObserver(&uiManager);
	ws.addObserver(&alertSystem);
	ws.addObserver(&logger);

	// Settings observers
	settingsMan.addObserver(&alertSystem);
	settingsMan.addObserver(&logger);

	// Pre loop so we don't wait for READ_INTERVAL in run_app on the first loop
	ws.update();
	ws.notifyObservers();
}
