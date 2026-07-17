#include "system_health.h"
#include "hardware_utils.h"
#include <array>
#include <string.h>

void SystemHealth::update() {
	if (HardwareUtils::timeElapsed(lastHealthCheckTime) >= INTERVAL) {
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
		if (comp && !comp->isOk()) {
			comp->runHealthCheck();
		}
	}

	lastHealthCheckTime = HardwareUtils::getTick();
}

void SystemHealth::healthCheckAll() {
	for (auto& comp : comps) {
		if (comp) {
			comp->runHealthCheck();
		}
	}

	lastHealthCheckTime = HardwareUtils::getTick();
}



