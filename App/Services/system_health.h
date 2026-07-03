#ifndef SERVICES_SYSTEM_HEALTH_H_
#define SERVICES_SYSTEM_HEALTH_H_

#include "health_checkable.h"
#include "utils.h"
#include <array>
#include <stdint.h>

using HealthSummary = std::array<char, 20>;

class SystemHealth {
	using ComponentsArray = std::array<IHealthCheckable*, 3>;
public:
	SystemHealth(const ComponentsArray& c) : comps(c) {}
	void update();
	HealthSummary getHealthSummary() const;
	bool allOk() const;
	void healthCheckFailed();
	void healthCheckAll();

private:
	static constexpr uint32_t INTERVAL = 1000;
	ComponentsArray comps;
	uint32_t lastHealthCheckTime = 0;
};

#endif /* SERVICES_SYSTEM_HEALTH_H_ */
