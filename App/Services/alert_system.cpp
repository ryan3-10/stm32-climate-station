#include "alert_system.h"

using STATE = ALERT_SYS_STATE;

void AlertSystem::update() {
	if (tempState == STATE::NO_TRIGGER && humState == STATE::NO_TRIGGER) {
		buzzer.stopPattern();
	} else {
		buzzer.runPattern();
	}
}

void AlertSystem::setConfig(const TempAlertConfig& t) {
	tempConfig = t;
	updateState();
}

void AlertSystem::setConfig(const HumAlertConfig& h) {
	humConfig = h;
	updateState();
}

void AlertSystem::onWeatherUpdate(const SensorRead& reading) {
	lastReading = reading;
	updateState();
}

void AlertSystem::updateState() {
	// return early if sensor is in an error state
	if (!lastReading.statusOk) {
		tempState = STATE::NO_TRIGGER;
		humState = STATE::NO_TRIGGER;
		return;
	}

	// check for temp triggers
	if (tempConfig.enabled) {
		if (lastReading.data.temp > tempConfig.maxTemp) {
			tempState = STATE::MAX_TRIGGER;
		} else if (lastReading.data.temp < tempConfig.minTemp) {
			tempState = STATE::MIN_TRIGGER;
		} else {
			tempState = STATE::NO_TRIGGER;
		}
	} else {
		tempState = STATE::NO_TRIGGER;
	}

	// check for humidity triggers
	if (humConfig.enabled) {
		if (lastReading.data.hum > humConfig.maxHum) {
			humState = STATE::MAX_TRIGGER;
		} else if (lastReading.data.hum < humConfig.minHum) {
			humState = STATE::MIN_TRIGGER;
		} else {
			humState = STATE::NO_TRIGGER;
		}
	} else {
		humState = STATE::NO_TRIGGER;
	}
}
