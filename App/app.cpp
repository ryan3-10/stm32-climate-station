#include "alert_system.h"
#include "app.h"
#include "ds3231_adapter.h"
#include "logger.h"
#include "settings_manager.h"
#include "sht31_adapter.h"
#include "system_health.h"
#include "utils.h"
#include "weather_station.h"
#include "ui_manager.h"
#include <stdint.h>
#include "Drivers/PassiveBuzzer/passive_buzzer.h"
#include "Drivers/Sht31/sht31.h"

#include "Drivers/Ds3231/ds3231.h"
#include "file_manager.h"

namespace {
	constexpr uint32_t READ_INTERVAL = 1000;
	constexpr uint32_t HEALTH_CHECK_INTERVAL = 1000;
	Sht31 sensor;
	Sht31Adapter sensorAdapter(sensor);
	WeatherStation ws(sensor);
	SettingsManager settingsMan;
	Ds3231 clock;
	Ds3231Adapter clockAdapter(clock);
	FileManager fileManager;
	Logger logger(settingsMan.getLogConfig(), clockAdapter, fileManager);
	PassiveBuzzer buzzer;
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig(), buzzer);
	UIManager uiManager(settingsMan);
	SystemHealth systemHealth({&sensorAdapter, &clockAdapter, &fileManager});
}

void run_app() {
	if (ws.timeSinceLastRead() >= READ_INTERVAL) {
		ws.update();
		ws.notifyObservers();
	}

	if (systemHealth.timeSinceLastCheck() >= HEALTH_CHECK_INTERVAL) {
		systemHealth.healthCheckFailed();
	}

	if (logger.needsToLog()) {
		logger.log<FileManager>(fileManager);
	}

	uiManager.updateHealthSummary(systemHealth.getHealthSummary());

	if (uiManager.isDirty()) {
		uiManager.render();
	}
	uiManager.handleInputs();
	alertSystem.update();
}

void init_app(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	// Late bind hardware
	SSD1306_Init();
	sensor.init(hi2c);
	clock.init(hi2c);
	fileManager.mount();
	fileManager.createFileIfNotExist("log.txt");
	buzzer.init(pvmTimer, TIM_CHANNEL_1);
	buzzer.setPattern(standardPattern2);

	// initial health check
	systemHealth.healthCheckAll();

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
