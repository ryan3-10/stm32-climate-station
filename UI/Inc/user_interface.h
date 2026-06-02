#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "data_structs.h"
#include "screen.h"
#include <array>

class UserInterface {
public:
	UserInterface(
		const LogConfig& logC,
		const TempAlertConfig& tAlertC,
		const HumAlertConfig& hAlertC
	);
	void toHome() { currentScreen = &homeScreen; }
	void toMenu() { currentScreen = &menuScreen; }
	void toSelected() { currentScreen = menuScreen.getSelection(); }
	bool needsRender() { return isDirty; }
	void render();
	void update(const WeatherData& data);
	EVENT_TYPE handlInput(INPUT_TYPE input);

private:
	std::array<Screen*, 4> menuItems = {
		&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen
	};

	bool isDirty = false;
	WeatherData weatherData;
	HomeScreen homeScreen;
	ConfigScreen logScreen;
	ConfigScreen tempAlertsScreen;
	ConfigScreen humAlertsScreen;
	MenuScreen menuScreen{menuItems};
	Screen* currentScreen = &homeScreen;
};


#endif /* USER_INTERFACE_H_ */
