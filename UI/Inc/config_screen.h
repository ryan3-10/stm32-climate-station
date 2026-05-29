#ifndef CONFIG_SCREEN_H_
#define CONFIG_SCREEN_H_

#include "screen.h"

class ConfigScreen : public Screen {
public:
	ConfigScreen(const CONFIG& c, const char* header, const char* label) :
		Screen(header, label), editConfig(c), masterConfig(c)
	{}

protected:
	void configHelper(const char* l1, const char* l2, const char* l3) const;
	CONFIG editConfig;
	uint8_t cursorPos = 0;

private:
	void cleanState() override;
	const CONFIG& masterConfig;
};


class LogConfigScreen : public ConfigScreen {
public:
	LogConfigScreen(const CONFIG& config)
		: ConfigScreen(config, "LOG CONFIG", "Log Config")
	{}

private:
	 void renderHelper() const override;
};

class AlertsConfigScreen : public ConfigScreen {
public:
	AlertsConfigScreen(const CONFIG& c, const char* header, const char* label)
		: ConfigScreen(c, header, label)
	{}

protected:
	 void alertsConfigHelper(uint16_t max, uint16_t min, char sign) const;
};

class TempAlertsConfigScreen : public AlertsConfigScreen {
public:
	TempAlertsConfigScreen(const CONFIG& config)
		: AlertsConfigScreen(config, "TEMP ALERTS", "Temp Alerts")
	{}

private:
	void renderHelper() const override;
};

class HumAlertsConfigScreen : public AlertsConfigScreen {
public:
	HumAlertsConfigScreen(const CONFIG& config)
		: AlertsConfigScreen(config, "HUM ALERTS", "Hum Alerts")
	{}

private:
	void renderHelper() const override;
};



#endif /* CONFIG_SCREEN_H_ */
