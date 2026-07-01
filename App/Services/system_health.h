#ifndef SERVICES_SYSTEM_HEALTH_H_
#define SERVICES_SYSTEM_HEALTH_H_

#include "ds3231_clock.h"
#include "file_manager.h"
#include "health_checkable.h"
#include "sht31_sensor.h"
#include "time_service.h"
#include <array>
#include <stdint.h>

using ComponentsArray = std::array<HealthCheckable*, 3>;
using HealthSummary = std::array<char, 20>;

class SystemHealth {
public:
	SystemHealth(const ComponentsArray& c) : comps(c) {}
	bool allOk() const;
	uint32_t timeSinceLastCheck() const { return timeElapsed(lastHealthCheckTime); }
	void healthCheckFailed();
	void healthCheckAll();
	HealthSummary getHealthSummary() const;

private:
	ComponentsArray comps;
	uint32_t lastHealthCheckTime = 0;
};

#endif /* SERVICES_SYSTEM_HEALTH_H_ */
