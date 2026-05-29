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

protected:
	static DisplayEngine engine;

private:
	virtual void renderHelper() const = 0;
	virtual void cleanState() = 0;
	const char* const header;
	const char* const label;
};

#endif /* INC_SCREEN_H_ */

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
