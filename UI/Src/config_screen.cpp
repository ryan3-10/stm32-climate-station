#include "display_engine.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>
#include <variant>

void configHelper(
	DisplayEngine* engine,
	const char* l1,
	const char* l2,
	const char* l3,
	uint8_t cursorPos
) {
	engine->setFont(FONT_SIZE::MED);
	engine->printLine(l1, cursorPos == 0);
	engine->printLine(l2, cursorPos == 1);

	engine->setFont(FONT_SIZE::SMALL);
	engine->printLine(l3, cursorPos == 2);
}

void alertsHelper(
	DisplayEngine* engine,
	bool enabled,
	uint16_t max,
	uint16_t min,
	char sign,
	uint8_t cursorPos
) {
	char line1[16];
	char line2[16];
	const char* line3 = enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "Max: %03i%c", max, sign);
	snprintf(line2, sizeof(line2), "Min: %03i%c", min, sign);

	configHelper(engine, line1, line2, line3, cursorPos);
}

void updateScreeNum(uint16_t& value, uint16_t max, INPUT_TYPE input) {
	switch (input) {
		case INPUT_TYPE::LEFT:
			value = value == 0 ? max : value - 1;
			break;
		case INPUT_TYPE::RIGHT:
			value = value == max ? 0 : value + 1;
			break;
		case INPUT_TYPE::ENTER:
			break;
	}
}

void updateScreenValue(ConfigValue& value, uint16_t maxNumValue, INPUT_TYPE input) {
	if (auto ptr = std::get_if<uint16_t*>(&value)) {
		updateScreeNum(**ptr, maxNumValue, input);
	}
	else if (auto ptr = std::get_if<bool*>(&value)) {
		auto& b = **ptr;
		b = !b;
	}
}

template <typename T>
UIEvent configHandleHelper(T& screen, UIEvent returnOnSubmit, INPUT_TYPE input) {
	UIEvent event = NullEvent{};

	if (input == INPUT_TYPE::ENTER) {
		if (screen.cursorPos == screen.configValues.size() - 1) {
			screen.cursorPos = 0;
			event = returnOnSubmit;
		} else {
			++screen.cursorPos;
		}
	}

	else {
		updateScreenValue(
			screen.configValues[screen.cursorPos],
			screen.MAX_CONFIG_VALUE,
			input
		);
	}

	return event;
}

UIEvent LogConfigScreen::handleInput(INPUT_TYPE input) {
	return configHandleHelper(*this, logConfig, input);
}

UIEvent TempAlertsScreen::handleInput(INPUT_TYPE input) {
	return configHandleHelper(*this, alertData, input);
}

UIEvent HumAlertsScreen::handleInput(INPUT_TYPE input) {
	return configHandleHelper(*this, alertData, input);
}

void LogConfigScreen::draw() const {
	char line1[16];
	char line2[16];
	const char* line3 = logConfig.enabled ? "Enabled" : "Disabled";

	snprintf(line1, sizeof(line1), "%02uh", logConfig.hourInt);
	snprintf(line2, sizeof(line2), "%02um", logConfig.minInt);

	configHelper(engine, line1, line2, line3, cursorPos);
}

void TempAlertsScreen::draw() const {
	alertsHelper(
		engine,
		alertData.tempEnabled,
		alertData.maxTemp,
		alertData.minTemp,
		'%',
		cursorPos
	);
}

void HumAlertsScreen::draw() const {
	alertsHelper(
		engine,
		alertData.humEnabled,
		alertData.maxHum,
		alertData.minHum,
		'%',
		cursorPos
	);
}
