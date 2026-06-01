#ifndef SCREEN_H_
#define SCREEN_H_

#include "data_structs.h"
#include "display_engine.h"
#include <array>
#include <variant>

class Screen;
struct NullEvent {};
struct LeftHome {};

enum class INPUT_TYPE : uint8_t {
	LEFT,
	ENTER,
	RIGHT
};

using UIEvent = std::variant<
	LeftHome,
	Logconfig,
	NullEvent,
	Screen*,
	WeatherData,
	AlertConfig
>;

using ConfigValue = std::variant<uint16_t*, bool*>;

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
	virtual UIEvent handleInput(INPUT_TYPE input) = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen() :
		Screen("Home")
	{}

	UIEvent handleInput(INPUT_TYPE input) override;
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

	UIEvent handleInput(INPUT_TYPE input) override;

private:
	 void draw() const override;

	 const menuArray& menu;
	 uint8_t cursorPos = 0;
};

class LogConfigScreen : public Screen {
	static constexpr uint16_t MAX_CONFIG_VALUE = 99;

public:
	LogConfigScreen(const Logconfig& lg)
		: Screen("Log Config")
		, logConfig(lg)
		,configValues({
			&logConfig.hourInt,
			&logConfig.minInt,
			&logConfig.enabled
		})
	{}

	UIEvent handleInput(INPUT_TYPE input) override;

private:
	 void draw() const override;
	 Logconfig logConfig;
	 uint8_t cursorPos = 0;
	 std::array<ConfigValue, 3> configValues;

	 template <typename T>
	 friend UIEvent configHandleHelper(T&, UIEvent, INPUT_TYPE);
};

class TempAlertsScreen : public Screen {
	static constexpr uint16_t MAX_CONFIG_VALUE = 999;

public:
	TempAlertsScreen(const AlertConfig& ad)
		: Screen("Temperature Alerts")
		, alertData(ad)
		, configValues({
			&alertData.maxTemp,
			&alertData.minTemp,
			&alertData.tempEnabled
		})
	{
	}

	UIEvent handleInput(INPUT_TYPE input) override;

private:
	void draw() const override;
	AlertConfig alertData;
	uint8_t cursorPos = 0;
	std::array<ConfigValue, 3> configValues;

	template <typename T>
	friend UIEvent configHandleHelper(T&, UIEvent, INPUT_TYPE);
};

class HumAlertsScreen : public Screen {
	static constexpr uint16_t MAX_CONFIG_VALUE = 100;

public:
	HumAlertsScreen(const AlertConfig& ad)
		: Screen("Humidity Alerts")
		, alertData(ad)
		, configValues({
			&alertData.maxHum,
			&alertData.minHum,
			&alertData.humEnabled
		})
	{}

	UIEvent handleInput(INPUT_TYPE input) override;

private:
	void draw() const override;
	AlertConfig alertData;
	uint8_t cursorPos = 0;
	std::array<ConfigValue, 3> configValues;

	template <typename T>
	friend UIEvent configHandleHelper(T&, UIEvent, INPUT_TYPE);
};

#endif

