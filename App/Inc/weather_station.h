#ifndef WEATHER_STATION_H_
#define WEATHER_STATION_H_

#include "observer.h"
#include "sht31_sensor.h"
#include <stdint.h>

class WeatherStation : public Subject {
public:
	WeatherStation(Sht31Sensor& s);

	float getHumidity() const;
	float getTemperature() const;
	void update();
	uint32_t getLastUpdate() const;

private:
	bool statusOk = true;

	float humidity = 0;
	float temperature = 0;

	Sht31Sensor& sensor;

	uint32_t lastUpdate = 0;

	bool meaningfulChange(SENSOR_DATA newData) const;
	virtual void notify() override;
	void setValues(SENSOR_DATA newData);
};



#endif /* WEATHER_DATA_H_ */
