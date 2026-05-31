#ifndef SCREEN_H_
#define SCREEN_H_

#include "data_structs.h"
#include "display_engine.h"
#include <array>

class Screen {
public:
	Screen(const char* l)
		: label(l)
	{}

	virtual ~Screen() = default;
	const char* getLabel() const { return label; }
	void render();
	static void init(DisplayEngine* e);

protected:
	static DisplayEngine* engine;

private:
	virtual void draw() const = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen() :
		Screen("Home")
	{}

	void update(const WeatherData& wd) { weatherData = wd; }

private:
	 void draw() const override;
	 WeatherData weatherData;
};

class MenuScreen : public Screen {
	static constexpr uint8_t MENU_LENGTH = 4;
	using menuArray = std::array<const Screen*, MENU_LENGTH>;

public:
	MenuScreen(const menuArray& m) :
		Screen("Menu"), menu(m)
	{}

private:
	 void draw() const override;

	 const menuArray& menu;
	 uint8_t cursorPos = 0;
};

class LogConfigScreen : public Screen {
public:
	LogConfigScreen(const LogData& lg)
		: Screen("Log Config"), logData(lg)
	{}

	virtual ~LogConfigScreen() = default;

private:
	 void draw() const override;
	 LogData logData;
	 uint8_t cursorPos = 0;
};

class TempAlertsScreen : public Screen {
public:
	TempAlertsScreen(const AlertData& ad)
		: Screen("Temperature Alerts"), alertData(ad)
	{}

private:
	void draw() const override;
	AlertData alertData;
	uint8_t cursorPos = 0;
};

class HumAlertsScreen : public Screen {
public:
	HumAlertsScreen(const AlertData& ad)
		: Screen("Humidity Alerts"), alertData(ad)
	{}

private:
	void draw() const override;
	AlertData alertData;
	uint8_t cursorPos = 0;
};

#endif

