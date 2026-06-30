#include "alert_system.h"

using STATE = ALERT_SYS_STATE;

void AlertSystem::update() {
	if (tempState == STATE::NO_TRIGGER && humState == STATE::NO_TRIGGER) {
		buzzer.stopPattern();
	} else {
		buzzer.runPattern();
	}
}

void AlertSystem::onWeatherUpdate(const SensorRead& reading) {
	// return early if sensor is in an error state
	if (!reading.statusOk) {
		tempState = STATE::NO_TRIGGER;
		humState = STATE::NO_TRIGGER;
		return;
	}

	// check for temp triggers
	if (tempConfig.enabled) {
		if (reading.data.temp > tempConfig.maxTemp) {
			tempState = STATE::MAX_TRIGGER;
		} else if (reading.data.temp < tempConfig.minTemp) {
			tempState = STATE::MIN_TRIGGER;
		} else {
			tempState = STATE::NO_TRIGGER;
		}
	} else {
		tempState = STATE::NO_TRIGGER;
	}

	// check for humidity triggers
	if (humConfig.enabled) {
		if (reading.data.hum > humConfig.maxHum) {
			humState = STATE::MAX_TRIGGER;
		} else if (reading.data.hum < humConfig.minHum) {
			humState = STATE::MIN_TRIGGER;
		} else {
			humState = STATE::NO_TRIGGER;
		}
	} else {
		humState = STATE::NO_TRIGGER;
	}
}

void AlertSystem::onSettingsChange(const Settings& settings) {
	humConfig = settings.humAlert;
	tempConfig = settings.tempAlert;
}

