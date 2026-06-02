#ifndef APP_CONTROLLER_H_
#define APP_CONTROLLER_H_

#include "circular_queue.h"
#include "settings.h"
#include "user_interface.h"
#include "weather_station.h"

class Controller {
public:
	Controller(WeatherStation w);
	void init();
	void run();
	void handleInputs();

private:
	Settings settings;
	WeatherStation ws;
	UserInterface ui;
	CircularQueue<INPUT_TYPE, 20> inputQ;
};

#endif /* APP_CONTROLLER_H_ */
