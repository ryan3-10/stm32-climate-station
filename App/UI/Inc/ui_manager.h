#ifndef UI_INC_UI_MANAGER_H_
#define UI_INC_UI_MANAGER_H_

#include "config_screen.h"
#include "display_engine.h"
#include "rotary_encoder.h"
#include "screen.h"
#include "settings_manager.h"

class UIManager {
public:
	UIManager(SettingsManager& sm) : settingsManager(sm) {}
	void handleInputs();
	void update();

private:
	void handleEvent(EVENT_TYPE event);
	void submitLogConfig();
	void submitTempConfig();
	void submitHumConfig();

	SettingsManager& settingsManager;
	RotaryEncoder rotaryEncoder;
	bool dirtyFlag = false;
	HomeScreen homeScreen;
	ConfigScreen logScreen{LogLayout(), EVENT_TYPE::LOG_CONFIG_SAVED};
	ConfigScreen tempAlertsScreen{TempAlertLayout(), EVENT_TYPE::TEMP_CONFIG_SAVED};
	ConfigScreen humAlertsScreen{HumAlertLayout(), EVENT_TYPE::HUM_CONFIG_SAVED};
	MenuScreen menuScreen{{&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen}};
	Screen* currentScreen = &homeScreen;
	DisplayEngine engine;
};




#endif /* UI_INC_UI_MANAGER_H_ */
