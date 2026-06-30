#ifndef SERVICES_SYSTEM_HEALTH_H_
#define SERVICES_SYSTEM_HEALTH_H_

#include "ds3231_clock.h"
#include "file_manager.h"
#include "sht31_sensor.h"
#include "time_service.h"
#include <stdint.h>

class SystemHealth {
public:
	SystemHealth(Sht31Sensor& sens, Ds3231Clock& clk, FileManager& fm)
		: sensor(sens)
		, clock(clk)
		, fileManager(fm)
	{}

	uint32_t timeSinceLastRetry() { return timeElapsed(lastRetryTime); }

	struct Snapshot {
		bool sensorOk;
		bool clockOk;
		bool fileManagerOk;

		bool operator!=(const Snapshot& other) const {
			return
				sensorOk != other.sensorOk ||
				clockOk != other.clockOk ||
				fileManagerOk != other.fileManagerOk;
		}
	};

	Snapshot getSnapshot() const;
	void retryFailedComponents();

private:
	Sht31Sensor& sensor;
	Ds3231Clock& clock;
	FileManager& fileManager;
	uint32_t lastRetryTime = 0;
};

#endif /* SERVICES_SYSTEM_HEALTH_H_ */
