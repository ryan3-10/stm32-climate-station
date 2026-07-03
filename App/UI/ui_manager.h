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
#include "ui_models.h"
#include <optional>

class UIManager : public WeatherObserver {
public:
	void handleInputs();
	std::optional<Submission> handleInput(INPUT_TYPE input);
	void onWeatherUpdate(const SensorRead& reading) override;
	void setHealthSummary(HealthSummary newSummary);
	void update();

private:
	struct ScreenSet {
		HomeScreen home;
		ConfigScreen log{LogLayout(), EVENT_TYPE::LOG_CONFIG_SAVED};
		ConfigScreen temp{TempAlertLayout(), EVENT_TYPE::TEMP_CONFIG_SAVED};
		ConfigScreen hum{HumAlertLayout(), EVENT_TYPE::HUM_CONFIG_SAVED};
		MenuScreen menu{{&home, &log, &temp, &hum}};
	};

	HealthSummary displayedHealth;
	bool dirtyFlag = true;
	ScreenSet screens;
	Screen* currentScreen = &screens.home;
	DisplayEngine engine;
};


#endif /* UI_INC_UI_MANAGER_H_ */
