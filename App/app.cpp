#include "app.h"
#include "sd.h"
#include "sht31_sensor.h"
#include "system.h"
#include "ui_manager.h"

namespace {
	constexpr uint32_t READ_INTERVAL = 1000;
	Sht31Sensor sensor;
	Sd sd;
	SettingsManager settingsMan;
	UIManager uiManager(settingsMan);
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig());
	LogSystem logSystem(settingsMan.getLogConfig());
}

void run_app() {
	if (sensor.timeSinceLastRead() >= READ_INTERVAL) {
		sensor.update();
		sensor.notifyObservers();
	}

	uiManager.update();
	uiManager.handleInputs();
}

void init_app(I2C_HandleTypeDef* hi2c, SPI_HandleTypeDef* spi) {
	// Late bind hardware
	SSD1306_Init();
	sensor.init(hi2c);
	sd.init(spi);

	// Weather observers
	sensor.addObserver(&uiManager);
	sensor.addObserver(&alertSystem);
	sensor.addObserver(&logSystem);

	// Settings observers
	settingsMan.addObserver(&alertSystem);
	settingsMan.addObserver(&logSystem);

	// Pre loop so we don't wait for READ_INTERVAL in run_app on the first loop
	sensor.update();
	sensor.notifyObservers();
	uiManager.update();
}
