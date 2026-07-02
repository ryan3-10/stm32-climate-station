#include "health_checkable.h"
#include "sht31_sensor.h"
#include "weather_sensor.h"

#ifndef ADAPTERS_SHT31_TO_HC_SENSOR_H_
#define ADAPTERS_SHT31_TO_HC_SENSOR_H_

class Sht31Adapter : public IHealthCheckable, public IWeatherSensor {
public:
	Sht31Adapter(Sht31Sensor& s) : sht31(s) {}
	const char* getErrorCode() const override { return "Se"; }
	bool isOk() const override { return sht31.getStatus() == Sht31Sensor::Status::Ok; }
	void runHealthCheck() override;
	bool getReading(WeatherData& wd) override;

private:
	Sht31Sensor& sht31;
};



#endif /* ADAPTERS_SHT31_TO_HC_SENSOR_H_ */
