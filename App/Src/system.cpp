#include "math.h"
#include "system.h"
#include <stm32f4xx_hal.h>

void AlertSystem::update(const WeatherData& weather) {
	using STATE = ALERT_SYS_STATE;

	// return early if sensor is in an error state
	if (!weather.statusOk) {
		tempState = STATE::NO_TRIGGER;
		humState = STATE::NO_TRIGGER;
		return;
	}

	// check for temp triggers
	if (tempConfig.enabled) {
		if (weather.temp > tempConfig.maxTemp) {
			tempState = STATE::MAX_TRIGGER;
		} else if (weather.temp < tempConfig.minTemp) {
			tempState = STATE::MIN_TRIGGER;
		} else {
			tempState = STATE::NO_TRIGGER;
		}
	}

	// check for humidity triggers
	if (humConfig.enabled) {
		if (weather.hum > humConfig.maxHum) {
			humState = STATE::MAX_TRIGGER;
		} else if (weather.hum < humConfig.minHum) {
			humState = STATE::MIN_TRIGGER;
		} else {
			humState = STATE::NO_TRIGGER;
		}
	}
}

void LogSystem::log() {
	// TODO implement logging logic
	lastLogTime = HAL_GetTick();
}

bool LogSystem::needsToLog() {
	if (!logConfig.enabled) {
		return false;
	}

	auto miliInterval = hoursToMili(logConfig.hourInt) + minToMili(logConfig.minInt);
	return HAL_GetTick() - lastLogTime >= miliInterval;
}

