#include "health_checkable.h"
#include "sht31.h"
#include "system_health.h"
#include "utils.h"
#include <array>
#include <string.h>
#include "ds3231.h"

void SystemHealth::update() {
	if (Utils::timeElapsed(lastHealthCheckTime) >= INTERVAL) {
		healthCheckFailed();
	}
}

HealthSummary SystemHealth::getHealthSummary() const {
	if (allOk()) {
		return HealthSummary {"System Ok"};
	}

	HealthSummary sum = {"Err:"};

	for (const auto& comp : comps) {
		if (!comp->isOk()) {
			// Concat a space char, and then the error code
			strncat(sum.data(), " ", sum.size() - strlen(sum.data()));
			strncat(sum.data(), comp->getErrorCode(), sum.size() - strlen(sum.data()));
		}
	}

	return sum;
}

bool SystemHealth::allOk() const {
	for (const auto& comp : comps) {
		if (!comp->isOk()) {
			return false;
		}
	}

	return true;
}

void SystemHealth::healthCheckFailed() {
	for (auto& comp : comps) {
		if (!comp->isOk()) {
			comp->runHealthCheck();
		}
	}

	lastHealthCheckTime = Utils::getTick();
}

void SystemHealth::healthCheckAll() {
	for (auto& comp : comps) {
		comp->runHealthCheck();
	}

	lastHealthCheckTime = Utils::getTick();
}



