#ifndef APP_CONTROLLER_H_
#define APP_CONTROLLER_H_

#include "system.h"
#include "circular_queue.h"
#include "settings.h"
#include "screen.h"
#include "weather_station.h"
#include <cassert>
#include <stdint.h>

class Controller {
public:
	Controller(WeatherStation w);
	void pushInput(INPUT_TYPE input) { assert(inputQ.push(input)); }
	void init();
	void run();

private:
	void handleInputs();
	void updateLogConfig(uint16_t hour, uint16_t min, bool en);
	void updateTempAlertConfig(uint16_t max, uint16_t min, bool en);
	void updateHumAlertConfig(uint16_t max, uint16_t min, bool en);

	Settings settings;
	WeatherStation ws;
	AlertSystem alertSys;
	LogSystem logSys;
	CircularQueue<INPUT_TYPE, 50> inputQ;

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
