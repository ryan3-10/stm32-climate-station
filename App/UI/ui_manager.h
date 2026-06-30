#ifndef UI_INC_UI_MANAGER_H_
#define UI_INC_UI_MANAGER_H_

#include "config_screen.h"
#include "display_engine.h"
#include "observer.h"
#include "rotary_encoder.h"
#include "screen.h"
#include "settings_manager.h"

struct SystemHealth {
	bool sensorOk = true;
	bool sdOk = true;
	bool clockOk = true;

	bool operator!=(const SystemHealth& other) const {
		return
			sensorOk != other.sensorOk ||
			sdOk != other.sdOk ||
			clockOk != other.clockOk;
	}
};

class UIManager : public WeatherObserver {
public:
	UIManager(SettingsManager& sm) : settingsManager(sm) {}
	void handleInputs();
	void renderIfDirty();
	void onWeatherUpdate(const SensorRead& reading) override;
	void updateHeaderInfo(const SystemHealth& sysHealth);

private:
	void handleEvent(EVENT_TYPE event);
	void submitLogConfig();
	void submitTempConfig();
	void submitHumConfig();

	SettingsManager& settingsManager;
	SystemHealth headerData;
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
