#include "health_checkable.h"
#include "weather_sensor.h"

#include "../Drivers/Sht31/sht31.h"

#ifndef ADAPTERS_SHT31_TO_HC_SENSOR_H_
#define ADAPTERS_SHT31_TO_HC_SENSOR_H_

class Sht31Adapter : public IHealthCheckable, public IWeatherSensor {
public:
	Sht31Adapter(Sht31& s) : sht31(s) {}
	const char* getErrorCode() const override { return "Se"; }
	bool isOk() const override { return sht31.getStatus() == Sht31::Status::Ok; }
	void runHealthCheck() override;
	bool getReading(WeatherData& wd) override;

private:
	Sht31& sht31;
};



#endif /* ADAPTERS_SHT31_TO_HC_SENSOR_H_ */
