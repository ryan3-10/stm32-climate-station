#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "app_config.h"
#include "observer.h"
#include "screen.h"
#include "weather_station.h"
#include <array>

class UserInterface : public Observer {
public:
	UserInterface(const APP_CONFIG& ac, const WeatherData& wd);
	void enable();
	void render();
	void update();

private:
	bool enabled = false;
	const APP_CONFIG& appConfig;
	const WeatherData& weatherData;
	HomeScreen homeScreen;
	LogConfigScreen logScreen;
	TempAlertsConfigScreen tempAlertsScreen;
	HumAlertsConfigScreen humAlertsScreen;

	std::array<Screen*, 4> menuItems = {
		&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen
	};

	MenuScreen menuScreen;
	Screen& currentScreen;


};


#endif /* USER_INTERFACE_H_ */
