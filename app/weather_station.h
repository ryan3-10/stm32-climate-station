#ifndef WEATHER_STATION_H_
#define WEATHER_STATION_H_

#include <stdint.h>

class WeatherStation {
private:
	float humidity;
	uint32_t lastRead;
	constexpr static uint32_t readInterval = 1000;
	float temperature;

	float rawToHumidity(uint8_t rawByte1, uint8_t rawByte2);
	float rawToTemperature(uint8_t rawByte1, uint8_t rawByte);
	void readData();
	WeatherStation();

public:
	~WeatherStation() = default;
	WeatherStation(const WeatherStation&) = delete;
	WeatherStation& operator=(const WeatherStation&) = delete;
	WeatherStation(WeatherStation&&) = delete;
	WeatherStation& operator=(WeatherStation&&) = delete;

	float getTemperature();
	float getHumidity();
	void update();
	static WeatherStation& getInstance();
};



#endif /* WEATHER_STATION_H_ */
