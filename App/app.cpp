#include "alert_system.h"
#include "app.h"
#include "logger.h"
#include "sht31_sensor.h"
#include "ui_manager.h"

namespace {
	constexpr uint32_t READ_INTERVAL = 1000;
	Sht31Sensor sensor;
	SettingsManager settingsMan;
	UIManager uiManager(settingsMan);
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig());
	Logger logger(settingsMan.getLogConfig());
}

void run_app() {
	if (sensor.timeSinceLastRead() >= READ_INTERVAL) {
		sensor.update();
		sensor.notifyObservers();
	}

	uiManager.update();
	uiManager.handleInputs();
}

void init_app(I2C_HandleTypeDef* hi2c) {
	// Late bind hardware
	SSD1306_Init();
	sensor.init(hi2c);

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
