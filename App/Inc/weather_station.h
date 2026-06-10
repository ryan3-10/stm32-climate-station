#ifndef APP_WEATHER_STATION_H_
#define APP_WEATHER_STATION_H_

#include "screen.h"
#include "settings.h"
#include "system.h"
#include <cassert>
#include <stdint.h>
#include "../Hardware/Inc/sht31_sensor.h"

class WeatherStation {
public:
	WeatherStation(Sht31Sensor& s);
	void init();
	void updateComponents();
	void handleInput(INPUT_TYPE input);

private:
	void updateLogConfig(uint16_t hour, uint16_t min, bool en);
	void updateTempAlertConfig(uint16_t max, uint16_t min, bool en);
	void updateHumAlertConfig(uint16_t max, uint16_t min, bool en);

	Settings settings;
	Sht31Sensor& sensor;
	AlertSystem alertSys;
	LogSystem logSys;

	bool uiDirty = false;
	HomeScreen homeScreen{&menuScreen};

	ConfigScreen logScreen{
	    LogLayout(),
	    &homeScreen,
	    [this](uint16_t hour, uint16_t min, bool en)
	    {
	        updateLogConfig(hour, min, en);
	    }
	};

	ConfigScreen tempAlertsScreen{
	    TempAlertLayout(),
	    &homeScreen,
	    [this](uint16_t max, uint16_t min, bool en)
	    {
	        updateTempAlertConfig(max, min, en);
	    }
	};

	ConfigScreen humAlertsScreen{
	    HumAlertLayout(),
	    &homeScreen,
	    [this](uint16_t max, uint16_t min, bool en)
	    {
	        updateHumAlertConfig(max, min, en);
	    }
	};

	std::array<Screen*, 4> menuItems = {
			&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen
	};

	MenuScreen menuScreen{menuItems};
	Screen* currentScreen = &homeScreen;
};


#endif /* APP_CONTROLLER_H_ */
