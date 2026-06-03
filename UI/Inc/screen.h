#ifndef SCREEN_H_
#define SCREEN_H_

#include "data_structs.h"
#include "display_engine.h"
#include <array>
#include <functional>

enum class INPUT_TYPE : uint8_t {
	LEFT,
	ENTER,
	RIGHT
};

struct ConfigScreenLayout {
	const char* header;
	uint16_t MAX_VALUE;
	const char* preData1;
	const char* preData2;
	const char postData;
};

class Screen {
public:
	Screen(const char* l)
		: label(l)
	{}

	virtual ~Screen() = default;
	virtual Screen* handleInput(INPUT_TYPE input) = 0;
	const char* getLabel() const { return label; }
	void render();
	static void init();

protected:
	// bad things happen if this is instantiated before hi2c
	inline static DisplayEngine* engine = nullptr;

private:
	virtual void draw() const = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen(Screen* next) : Screen("Home"), nextScreen(next) {}

	Screen* handleInput(INPUT_TYPE input) override;
	void update(const WeatherData& w) { weather = w; }

private:
	 void draw() const override;
	 WeatherData weather;
	 Screen* nextScreen;
};

class MenuScreen : public Screen {
	static constexpr uint8_t MENU_LENGTH = 4;
	using menuArray = std::array<Screen*, MENU_LENGTH>;

public:
	MenuScreen(menuArray& m) :
		Screen("Menu"), menu(m)
	{}

	Screen* handleInput(INPUT_TYPE input) override;

private:
	 void draw() const override;

	 Screen* selection = nullptr;
	 const menuArray& menu;
	 uint8_t cursorPos = 0;
};

class ConfigScreen : public Screen {
	static constexpr uint8_t NUM_ITEMS = 3;
	using OnSaveCallback = std::function<void(uint16_t, uint16_t, bool)>;

public:
	ConfigScreen(const ConfigScreenLayout& lay, Screen* next, OnSaveCallback os)
		: Screen(lay.header)
		, layout(lay)
		, nextScreen(next)
		, onSave(os)
	{}

	Screen* handleInput(INPUT_TYPE input) override;

private:
	 void draw() const override;
	 void stepUp();
	 void stepDown();

	 const ConfigScreenLayout layout;
	 uint16_t d1 = 0;
	 uint16_t d2 = 0;
	 bool en = false;
	 uint8_t cursorPos = 0;
	 Screen* nextScreen;
	 OnSaveCallback onSave;
};

ConfigScreenLayout LogLayout();
ConfigScreenLayout TempAlertLayout();
ConfigScreenLayout HumAlertLayout();

#endif

