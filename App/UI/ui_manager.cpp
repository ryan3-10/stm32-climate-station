#include "ui_manager.h"
#include "ui_models.h"
#include "system_health.h"
#include <optional>

void UIManager::update() {
	if (dirtyFlag) {
		currentScreen->render(engine, displayedHealth.data());
		dirtyFlag = false;
	}
}

std::optional<Submission> UIManager::handleInput(INPUT_TYPE input) {
	std::optional<Submission> result = std::nullopt;
	auto event = currentScreen->handleInput(input);

	switch (event) {
	case EVENT_TYPE::NONE:
		break;
	case EVENT_TYPE::HOME_LEFT:
		currentScreen = &screens.menu;
		break;
	case EVENT_TYPE::MENU_ITEM_SELECTED:
		currentScreen = screens.menu.getSelection();
		break;
	case EVENT_TYPE::LOG_CONFIG_SAVED:
		result = {SubmissionType::Log, screens.log.getConfigEdit()};
		currentScreen = &screens.home;
		break;
	case EVENT_TYPE::TEMP_CONFIG_SAVED:
		result = {SubmissionType::Temp, screens.temp.getConfigEdit()};
		currentScreen = &screens.home;
		break;
	case EVENT_TYPE::HUM_CONFIG_SAVED:
		result = {SubmissionType::Hum, screens.hum.getConfigEdit()};
		currentScreen = &screens.home;
		break;
	}

	dirtyFlag = true;
	return result;
}

void UIManager::setHealthSummary(HealthSummary newSummary) {
	if (newSummary != displayedHealth) {
		displayedHealth = newSummary;
		dirtyFlag = true;
	}
}

void UIManager::onWeatherUpdate(const SensorRead& reading) {
	screens.home.update(reading);
	if (currentScreen == &screens.home) {
		dirtyFlag = true;
	}
}
