#include "health_checkable.h"
#include "sht31.h"
#include "weather_sensor.h"

#ifndef ADAPTERS_SHT31_TO_HC_SENSOR_H_
#define ADAPTERS_SHT31_TO_HC_SENSOR_H_

class Sht31Sensor : public IHealthCheckable, public IWeatherSensor {
public:
	Sht31Sensor(Sht31& s) : sht31(s) {}
	const char* getErrorCode() const override { return "Se"; }
	bool isOk() const override { return sht31.getStatus() == Sht31::Status::Ok; }
	void runHealthCheck() override;
	bool getReading(WeatherData& wd) override;

private:
	Sht31& sht31;
};



#endif /* ADAPTERS_SHT31_TO_HC_SENSOR_H_ */
