#ifndef SERVICES_SYSTEM_HEALTH_H_
#define SERVICES_SYSTEM_HEALTH_H_

#include "health_checkable.h"
#include "utils.h"
#include <array>
#include <stdint.h>
#include "ds3231.h"
#include "sht31.h"

using ComponentsArray = std::array<IHealthCheckable*, 3>;
using HealthSummary = std::array<char, 20>;

class SystemHealth {
public:
	SystemHealth(const ComponentsArray& c) : comps(c) {}
	bool allOk() const;
	uint32_t timeSinceLastCheck() const { return Utils::timeElapsed(lastHealthCheckTime); }
	void healthCheckFailed();
	void healthCheckAll();
	HealthSummary getHealthSummary() const;

private:
	ComponentsArray comps;
	uint32_t lastHealthCheckTime = 0;
};

#endif /* SERVICES_SYSTEM_HEALTH_H_ */
