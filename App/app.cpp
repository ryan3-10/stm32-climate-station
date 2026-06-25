#include "alert_system.h"
#include "app.h"
#include "logger.h"
#include "passive_buzzer.h"
#include "settings_manager.h"
#include "sht31_sensor.h"
#include "ui_manager.h"
#include "ds3231_clock.h"

namespace {
	constexpr uint32_t READ_INTERVAL = 1000;
	Sht31Sensor sensor;
	SettingsManager settingsMan;
	Ds3231Clock clock;
	Logger logger(settingsMan.getLogConfig(), clock);
	PassiveBuzzer buzzer;
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig());
	UIManager uiManager(settingsMan);
}

void run_app() {
	if (sensor.timeSinceLastRead() >= READ_INTERVAL) {
		sensor.update();
		sensor.notifyObservers();
	}

	if (logger.needsToLog()) {
		logger.log();
	}

	uiManager.update();
	uiManager.handleInputs();
}

void init_app(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	// Late bind hardware
	SSD1306_Init();
	sensor.init(hi2c);
	clock.init(hi2c);
	logger.init();
	buzzer.init(pvmTimer, TIM_CHANNEL_1);

	// Weather observers
	sensor.addObserver(&uiManager);
	sensor.addObserver(&alertSystem);
	sensor.addObserver(&logger);

	// Settings observers
	settingsMan.addObserver(&alertSystem);
	settingsMan.addObserver(&logger);

	// Pre loop so we don't wait for READ_INTERVAL in run_app on the first loop
	sensor.update();
	sensor.notifyObservers();
	uiManager.update();
}
