#include "alert_system.h"
#include "app.h"
#include "ds3231_clock.h"
#include "ds3231.h"
#include "file_manager.h"
#include "logger.h"
#include "passive_buzzer.h"
#include "settings_manager.h"
#include "sht31.h"
#include "sht31_sensor.h"
#include "system_health.h"
#include "ui_manager.h"
#include "ui_models.h"
#include "utils.h"
#include "weather_station.h"
#include <stdint.h>

namespace {
	Sht31 sht31;
	Sht31Sensor sensor(sht31);
	WeatherStation ws(sensor);
	SettingsManager settingsMan;
	Ds3231 clock;
	Ds3231Clock clockAdapter(clock);
	FileManager fileManager;
	Logger<FileManager> logger(settingsMan.getLogConfig(), clockAdapter, fileManager);
	PassiveBuzzer buzzer;
	AlertSystem alertSystem(settingsMan.getTempConfig(), settingsMan.getHumConfig(), buzzer);
	UIManager ui;
	RotaryEncoder rotEncoder;
	SystemHealth systemHealth({&sensor, &clockAdapter, &fileManager});
}

void handleSubmission(Submission sub) {
	auto [d1, d2, en] = sub.config;

	switch (sub.type) {
	case SubmissionType::Log:
		logger.setConfig({d1, d2, en});
		break;
	case SubmissionType::Temp:
		alertSystem.setConfig(TempAlertConfig{d1, d2, en});
		break;
	case SubmissionType::Hum:
		alertSystem.setConfig(HumAlertConfig{d1, d2, en});
		break;
	}
}

void handleInputs() {
	// Handle button press
	if (rotEncoder.buttonWasPressed()) {
		auto sub = ui.handleInput(INPUT_TYPE::ENTER);
		if (sub) {
			handleSubmission(*sub);
		}
	}

	// Handle rotary click inputs
	auto localEncoderPos = rotEncoder.readPos();
	if (localEncoderPos != 0) {
		INPUT_TYPE input = localEncoderPos > 0 ? INPUT_TYPE::RIGHT : INPUT_TYPE::LEFT;

		uint32_t absoluteClicks = std::abs(localEncoderPos);
		for (uint32_t i = 0; i < absoluteClicks; ++i) {
			ui.handleInput(input);
		}
	}
}

void run_app() {
	ws.update();
	systemHealth.update();
	logger.update();
	ui.setHealthSummary(systemHealth.getHealthSummary());
	ui.update();
	handleInputs();
	alertSystem.update();
}

void init_app(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	// Late bind hardware
	SSD1306_Init();
	sht31.init(hi2c);
	clock.init(hi2c);
	fileManager.mount();
	fileManager.createFileIfNotExist("log.txt");
	buzzer.init(pvmTimer, TIM_CHANNEL_1);
	buzzer.setPattern(standardPattern2);

	// Weather observers
	ws.addObserver(&ui);
	ws.addObserver(&alertSystem);
	ws.addObserver(&logger);

	// initial health check
	systemHealth.healthCheckAll();

	// Initial ws run so we don't wait in run_app on the first read
	ws.init();
}
