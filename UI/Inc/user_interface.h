#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "app_config.h"
#include "display_engine.h"
#include "observer.h"
#include "weather_station.h"

class UserInterface : public Observer {
public:
	UserInterface(const APP_CONFIG& ac, const WeatherData& wd)
		: appConfig(ac), weatherData(wd)
	{}
	void render();
	void update();

private:
	const APP_CONFIG& appConfig;
	const WeatherData& weatherData;
};


#endif /* USER_INTERFACE_H_ */
