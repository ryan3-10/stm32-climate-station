#include "ui_manager.h"

void UIManager::update() {
	if (dirtyFlag) {
		currentScreen->render(engine);
		dirtyFlag = false;
	}
}

void UIManager::handleInputs() {
	// handle button press
	if (rotaryEncoder.buttonWasPressed()) {
		dirtyFlag = true;
		auto event = currentScreen->handleInput(INPUT_TYPE::ENTER);
		handleEvent(event);
	}

	// Handle rotary click inputs
	auto localEncoderPos = rotaryEncoder.readPos();
	if (localEncoderPos != 0) {
		dirtyFlag = true;
		INPUT_TYPE input = localEncoderPos > 0 ? INPUT_TYPE::RIGHT : INPUT_TYPE::LEFT;

		uint32_t absoluteClicks = std::abs(localEncoderPos);
		for (uint32_t i = 0; i < absoluteClicks; ++i) {
			currentScreen->handleInput(input);
		}
	}
}

void UIManager::handleEvent(EVENT_TYPE event) {
	switch (event) {
	case EVENT_TYPE::NONE:
		break;
	case EVENT_TYPE::HOME_LEFT:
		currentScreen = &menuScreen;
		break;
	case EVENT_TYPE::MENU_ITEM_SELECTED:
		currentScreen = menuScreen.getSelection();
		break;
	case EVENT_TYPE::LOG_CONFIG_SAVED:
		submitLogConfig();
		currentScreen = &homeScreen;
		break;
	case EVENT_TYPE::TEMP_CONFIG_SAVED:
		submitTempConfig();
		currentScreen = &homeScreen;
		break;
	case EVENT_TYPE::HUM_CONFIG_SAVED:
		submitHumConfig();
		currentScreen = &homeScreen;
		break;
	}
}

void UIManager::submitLogConfig() {
	logScreen.submitChanges(
		[this] (uint16_t d1, uint16_t d2, bool en)
		{
			settingsManager.setLogConfig({d1, d2, en});
		}
	);
	settingsManager.notifyObservers();
}

void UIManager::submitTempConfig() {
	tempAlertsScreen.submitChanges(
		[this] (uint16_t d1, uint16_t d2, bool en)
		{
			settingsManager.setTempConfig({d1, d2, en});
		}
	);
	settingsManager.notifyObservers();
}

void UIManager::submitHumConfig() {
	humAlertsScreen.submitChanges(
		[this] (uint16_t d1, uint16_t d2, bool en)
		{
			settingsManager.setHumConfig({d1, d2, en});
		}
	);
	settingsManager.notifyObservers();
}

void UIManager::onWeatherUpdate(const SensorRead& reading) {
	homeScreen.update(reading);
	if (currentScreen == &homeScreen) {
		dirtyFlag = true;
	}
}
