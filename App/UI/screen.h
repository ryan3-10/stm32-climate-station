#ifndef SCREEN_H_
#define SCREEN_H_

#include <array>
#include "config_models.h"
#include "display_engine.h"
#include "system_health.h"
#include "weather_models.h"
#include "ui_models.h"

class Screen {
public:
	Screen(const char* l) : label(l) {}

	virtual ~Screen() = default;
	virtual EVENT_TYPE handleInput(INPUT_TYPE input) = 0;
	const char* getLabel() const { return label; }
	void render(DisplayEngine& engine, const char* header);

private:
	virtual void drawBody(DisplayEngine& engine) const = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen() : Screen("Home") {}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	void update(const SensorRead& r) { reading = r; }

private:
	 void drawBody(DisplayEngine& engine) const override;
	 SensorRead reading;
};

class MenuScreen : public Screen {
	static constexpr uint8_t MENU_LENGTH = 4;
	using menuArray = std::array<Screen*, MENU_LENGTH>;

public:
	MenuScreen(const menuArray& m) : Screen("Menu"), menu(m) {}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	Screen* getSelection() { return selection; }

private:
	 void drawBody(DisplayEngine& engine) const override;

	 Screen* selection = nullptr;
	 const menuArray menu;
	 uint8_t cursorPos = 0;
};

#endif

