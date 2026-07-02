#ifndef MODELS_WEATHER_MODELS_H_
#define MODELS_WEATHER_MODELS_H_

struct WeatherData {
	float temp = 0.0f;
	float hum = 0.0f;
};

struct SensorRead {
	WeatherData data;
	bool statusOk;
};

#endif /* MODELS_WEATHER_MODELS_H_ */
