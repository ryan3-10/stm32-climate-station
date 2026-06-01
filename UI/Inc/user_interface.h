#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "data_structs.h"
#include "display_engine.h"
#include "observer.h"
#include "screen.h"
#include <array>

class UserInterface : public Observer {
public:
	UserInterface(const SettingsConfig& ac);
	bool needsRender() { return isDirty; }
	void render();
	void update(const WeatherData& data) override;

private:
	std::array<Screen*, 4> menuItems = {
		&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen
	};

	bool isDirty = false;
	WeatherData weatherData;
	LogConfig logC;
	TempAlertConfig tempC;
	HumAlertConfig humC;
	HomeScreen homeScreen;
	ConfigScreen logScreen;
	ConfigScreen tempAlertsScreen;
	ConfigScreen humAlertsScreen;
	MenuScreen menuScreen;
	Screen& currentScreen;
};


#endif /* USER_INTERFACE_H_ */
