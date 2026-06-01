#ifndef SCREEN_H_
#define SCREEN_H_

#include "data_structs.h"
#include "display_engine.h"
#include <array>

enum class INPUT_TYPE : uint8_t {
	LEFT,
	ENTER,
	RIGHT
};

enum class EVENT_TYPE : uint8_t {
	NULL_EVENT,
	LEFT_HOME,
	MENU_SELECT,
	LOG_CONFIG_SAVE,
	TEMP_CONFIG_SAVE,
	HUM_CONFIG_SAVE
};

struct ConfigScreenLayout {
	const char* header;
	const uint16_t MAX_VALUE;
	const uint8_t MIN_DATA_WIDTH;
	const char* preData1;
	const char* preData2;
	const char postData;
	const EVENT_TYPE onSave;
};

class Screen {
public:
	Screen(const char* l)
		: label(l)
	{}

	virtual ~Screen() = default;
	const char* getLabel() const { return label; }
	void render();
	static void init();

protected:
	inline static DisplayEngine* engine = nullptr;

private:
	virtual void draw() const = 0;
	virtual EVENT_TYPE handleInput(INPUT_TYPE input) = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen() : Screen("Home") {}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	void update(const WeatherData& wd) { weatherData = wd; }

private:
	 void draw() const override;
	 WeatherData weatherData;
};

class MenuScreen : public Screen {
	static constexpr uint8_t MENU_LENGTH = 4;
	using menuArray = std::array<Screen*, MENU_LENGTH>;

public:
	MenuScreen(menuArray& m) :
		Screen("Menu"), menu(m)
	{}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	Screen* getSelection() { return selection; }

private:
	 void draw() const override;

	 Screen* selection = nullptr;
	 const menuArray& menu;
	 uint8_t cursorPos = 0;
};

class ConfigScreen : public Screen {
	static constexpr uint8_t NUM_ITEMS = 3;

public:
	ConfigScreen(LogConfig& con, const ConfigScreenLayout& lay)
		: Screen(lay.header)
		, layout(lay)
		, d1(con.hourInt)
		, d2(con.minInt)
		, en(con.enabled)
		{

		}

	ConfigScreen(TempAlertConfig& con, const ConfigScreenLayout& lay)
		: Screen(lay.header)
		, layout(lay)
		, d1(con.minTemp)
		, d2(con.maxTemp)
		, en(con.enabled)
		{

		}

	ConfigScreen(HumAlertConfig& con, const ConfigScreenLayout& lay)
		: Screen(lay.header)
		, layout(lay)
		, d1(con.minHum)
		, d2(con.maxHum)
		, en(con.enabled)
		{

		}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;

private:
	 void draw() const override;
	 void stepUp();
	 void stepDown();

	 ConfigScreenLayout layout;
	 uint16_t& d1;
	 uint16_t& d2;
	 bool& en;
	 uint8_t cursorPos = 0;
};

#endif

