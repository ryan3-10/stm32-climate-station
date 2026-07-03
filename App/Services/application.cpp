#include "application.h"
#include "ui_models.h"

void Application::run() {
	ws.update();
	systemHealth.update();
	logger.update();
	ui.setHealthSummary(systemHealth.getHealthSummary());
	ui.update();
	handleInputs();
	alertSystem.update();
}

void Application::init(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* pvmTimer) {
	// Late bind hardware
	SSD1306_Init();
	sht31.init(hi2c);
	ds3231.init(hi2c);
	fileManager.mount();
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

void Application::handleSubmission(Submission sub) {
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

void Application::handleInputs() {
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
