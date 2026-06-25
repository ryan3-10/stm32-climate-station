#ifndef SERVICES_INC_ALERT_SYSTEM_H_
#define SERVICES_INC_ALERT_SYSTEM_H_

#include "data_structs.h"
#include "observer.h"
#include "passive_buzzer.h"

enum class ALERT_SYS_STATE : uint8_t {
	NO_TRIGGER,
	MAX_TRIGGER,
	MIN_TRIGGER
};

class AlertSystem : public WeatherObserver, public SettingsObserver {
public:
	AlertSystem(const TempAlertConfig& t, const HumAlertConfig& h, PassiveBuzzer& pb)
		: tempConfig(t), humConfig(h), buzzer(pb)
	{}

	~AlertSystem() = default;

	void update();
	void onWeatherUpdate(const WeatherData& weather) override;
	void onSettingsChange(const Settings& settings) override;
	void setConfig(const TempAlertConfig& t) { tempConfig = t; }
	void setConfig(const HumAlertConfig& h) { humConfig = h; }
	ALERT_SYS_STATE getTempState() const { return tempState; }
	ALERT_SYS_STATE getHumState() const { return humState; }

private:
	TempAlertConfig tempConfig;
	HumAlertConfig humConfig;
	PassiveBuzzer& buzzer;
	ALERT_SYS_STATE tempState = ALERT_SYS_STATE::NO_TRIGGER;
	ALERT_SYS_STATE humState = ALERT_SYS_STATE::NO_TRIGGER;
};

#endif /* SRC_SYSTEM_H_ */
