#include "app.h"
#include "sht31_sensor.h"
#include "system.h"
#include "ui_manager.h"

namespace {
	Sht31Sensor sensor;
	SettingsManager settingsMan;
	UIManager uiManager(settingsMan);
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig());
	LogSystem logSystem(settingsMan.getLogConfig());
}

void run_app(I2C_HandleTypeDef* hi2c) {
	// Late bind hardware
	sensor.init(hi2c);
	sensor.addObserver(&uiManager);
	sensor.addObserver(&alertSystem);
	sensor.addObserver(&logSystem);

	sensor.update();
	sensor.notifyObservers();

	constexpr uint32_t READ_INTERVAL = 1000;
	while (true) {
		if (sensor.timeSinceLastRead() >= READ_INTERVAL) {
			sensor.update();
			sensor.notifyObservers();
		}

		uiManager.update();
		uiManager.handleInputs();
	}
}
