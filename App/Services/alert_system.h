#ifndef SERVICES_INC_ALERT_SYSTEM_H_
#define SERVICES_INC_ALERT_SYSTEM_H_

#include "config_models.h"
#include "observer.h"
#include "passive_buzzer.h"

enum class ALERT_SYS_STATE : uint8_t {
	NO_TRIGGER,
	MAX_TRIGGER,
	MIN_TRIGGER
};

class AlertSystem : public Observer {
public:
	AlertSystem(PassiveBuzzer& b) : buzzer(b) {}
	void update();
	void onWeatherUpdate(const SensorRead& reading) override;
	void setConfig(const TempAlertConfig& t);
	void setConfig(const HumAlertConfig& h);
	ALERT_SYS_STATE getTempState() const { return tempState; }
	ALERT_SYS_STATE getHumState() const { return humState; }

private:
	void updateState();

	PassiveBuzzer& buzzer;
	SensorRead lastReading{};
	TempAlertConfig tempConfig{};
	HumAlertConfig humConfig{};
	ALERT_SYS_STATE tempState = ALERT_SYS_STATE::NO_TRIGGER;
	ALERT_SYS_STATE humState = ALERT_SYS_STATE::NO_TRIGGER;
};

#endif /* SRC_SYSTEM_H_ */
