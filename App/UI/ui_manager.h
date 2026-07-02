#ifndef UI_INC_UI_MANAGER_H_
#define UI_INC_UI_MANAGER_H_

#include "config_screen.h"
#include "system_health.h"
#include "observer.h"
#include "screen.h"
#include "settings_manager.h"
#include "system_health.h"
#include "display_engine.h"
#include "rotary_encoder.h"

class UIManager : public WeatherObserver {
public:
	UIManager(SettingsManager& sm) : settingsManager(sm) {}
	void handleInputs();
	void render();
	void onWeatherUpdate(const SensorRead& reading) override;
	void updateHealthSummary(HealthSummary newSummary);
	bool isDirty() { return dirtyFlag; }

private:
	void handleEvent(EVENT_TYPE event);
	void submitLogConfig();
	void submitTempConfig();
	void submitHumConfig();

	SettingsManager& settingsManager;
	HealthSummary currentlyDisplayedHealth;
	RotaryEncoder rotaryEncoder;
	bool dirtyFlag = true;
	HomeScreen homeScreen;
	ConfigScreen logScreen{LogLayout(), EVENT_TYPE::LOG_CONFIG_SAVED};
	ConfigScreen tempAlertsScreen{TempAlertLayout(), EVENT_TYPE::TEMP_CONFIG_SAVED};
	ConfigScreen humAlertsScreen{HumAlertLayout(), EVENT_TYPE::HUM_CONFIG_SAVED};
	MenuScreen menuScreen{{&homeScreen, &logScreen, &tempAlertsScreen, &humAlertsScreen}};
	Screen* currentScreen = &homeScreen;
	DisplayEngine engine;
};


#endif /* UI_INC_UI_MANAGER_H_ */
