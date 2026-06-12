#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_

#include "data_structs.h"

enum class ALERT_SYS_STATE : uint8_t {
	NO_TRIGGER,
	MAX_TRIGGER,
	MIN_TRIGGER
};

class AlertSystem {
public:
	AlertSystem(const TempAlertConfig& t, const HumAlertConfig& h)
		: tempConfig(t), humConfig(h)
	{}

	~AlertSystem() = default;

	void update(const WeatherData& weather);
	void setConfig(const TempAlertConfig& t) { tempConfig = t; }
	void setConfig(const HumAlertConfig& h) { humConfig = h; }
	ALERT_SYS_STATE getTempState() const { return tempState; }
	ALERT_SYS_STATE getHumState() const { return humState; }

private:
	TempAlertConfig tempConfig;
	HumAlertConfig humConfig;
	ALERT_SYS_STATE tempState = ALERT_SYS_STATE::NO_TRIGGER;
	ALERT_SYS_STATE humState = ALERT_SYS_STATE::NO_TRIGGER;
};

class LogSystem {
public:
	LogSystem(const LogConfig& l) : logConfig(l) {}
	~LogSystem() = default;

	void log();
	void setConfig(const LogConfig& l) { logConfig = l; }
	void update(const WeatherData& weather) { cachedWeather = weather; }
	bool needsToLog() const;

private:
	LogConfig logConfig;
	uint32_t lastLogTime;
	uint32_t miliInterval;
	WeatherData cachedWeather;
};

#endif /* SRC_SYSTEM_H_ */
