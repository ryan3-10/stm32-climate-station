#ifndef UI_INC_UI_MANAGER_H_
#define UI_INC_UI_MANAGER_H_

#include "config_screen.h"
#include "display_engine.h"
#include "observer.h"
#include "screen.h"
#include "system_health.h"
#include "ui_models.h"
#include <optional>

class UIManager : public Observer {
public:
	void handleInputs();
	std::optional<Submission> handleInput(INPUT_TYPE input);
	void onWeatherUpdate(const SensorRead& reading) override;
	void setHealthSummary(HealthSummary newSummary);
	void update();

private:
	struct ScreenSet {
		HomeScreen home;
		ConfigScreen log{logLayout, EVENT_TYPE::LOG_CONFIG_SAVED};
		ConfigScreen temp{tempAlertLayout, EVENT_TYPE::TEMP_CONFIG_SAVED};
		ConfigScreen hum{humAlertLayout, EVENT_TYPE::HUM_CONFIG_SAVED};
		MenuScreen menu{{&home, &log, &temp, &hum}};
	};

	HealthSummary displayedHealth;
	bool dirtyFlag = true;
	ScreenSet screens;
	Screen* currentScreen = &screens.home;
	DisplayEngine engine;
};


#endif /* UI_INC_UI_MANAGER_H_ */
