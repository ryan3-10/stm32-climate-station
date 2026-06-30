#include "ds3231_clock.h"
#include "file_manager.h"
#include "sht31_sensor.h"
#include "system_health.h"
#include "time_service.h"

SystemHealth::Snapshot SystemHealth::getSnapshot() const {
	return SystemHealth::Snapshot {
		sensor.getStatus() == SENSOR_STATUS::OK,
		clock.getStatus() == CLOCK_STATUS::OK,
		!fileManager.isHardwareErr()
	};
}

void SystemHealth::retryFailedComponents() {
	if (sensor.getStatus() != SENSOR_STATUS::OK) {
		float _;
		sensor.getTempFAndHum(_, _);
	}

	if (clock.getStatus() != CLOCK_STATUS::OK) {
		DateTime _;
		clock.currentDateTime(_);
	}

	if (fileManager.isHardwareErr()) {
		fileManager.mount();
		fileManager.createFileIfNotExist("log.txt");
	}

	lastRetryTime = getTick();
}



