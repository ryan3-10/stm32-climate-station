#include "ds3231_clock.h"
#include "file_manager.h"
#include "health_checkable.h"
#include "sht31_sensor.h"
#include "system_health.h"
#include "time_service.h"
#include <array>
#include <string.h>

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

	lastHealthCheckTime = getTick();
}

void SystemHealth::healthCheckAll() {
	for (auto& comp : comps) {
		comp->runHealthCheck();
	}

	lastHealthCheckTime = getTick();
}



