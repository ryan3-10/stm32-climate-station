#ifndef SCREEN_H_
#define SCREEN_H_

#include "app_config.h"
#include "display_engine.h"
#include "weather_station.h"
#include <array>

class Screen {
public:
	Screen(const char* h, const char* l)
		: header(h), label(l)
	{}

	virtual ~Screen() = default;
	const char* getHeader() const { return header; }
	const char* getLabel() const { return label; }
	void render(bool freshRender);
	static void init();

protected:
	static DisplayEngine* engine;

private:
	virtual void renderHelper() const = 0;
	virtual void cleanState() = 0;
	const char* const header;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen(const WeatherData& wd) :
		Screen("HOME", "Home"), weatherData(wd)
	{}

private:
	 void renderHelper() const override;
	 void cleanState() override {} // nothing to clear for the home screen

	 const WeatherData& weatherData;
};

class MenuScreen : public Screen {
	static constexpr uint8_t MENU_LENGTH = 4;

public:
	MenuScreen(const std::array<Screen*, MENU_LENGTH>& m) :
		Screen("MENU", "Menu"), menu(m)
	{}

private:
	 void renderHelper() const override;
	 void cleanState() override { cursorPos = 0; }

	 const std::array<Screen*, MENU_LENGTH>& menu;
	 uint8_t cursorPos = 0;
};

class ConfigScreen : public Screen {
public:
	ConfigScreen(const CONFIG& c, const char* header, const char* label) :
		Screen(header, label), editConfig(c), masterConfig(c)
	{}
	virtual ~ConfigScreen() = default;

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
	virtual ~LogConfigScreen() = default;

private:
	 void renderHelper() const override;
};

class AlertsConfigScreen : public ConfigScreen {
public:
	AlertsConfigScreen(const CONFIG& c, const char* header, const char* label)
		: ConfigScreen(c, header, label)
	{}
	virtual ~AlertsConfigScreen() = default;

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

#endif

