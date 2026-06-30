#ifndef SCREEN_H_
#define SCREEN_H_

#include "data_structs.h"
#include "display_engine.h"
#include <array>
#include <optional>

enum class INPUT_TYPE : uint8_t {
	LEFT,
	ENTER,
	RIGHT
};

enum class EVENT_TYPE : uint8_t {
	NONE,
	HOME_LEFT,
	MENU_ITEM_SELECTED,
	LOG_CONFIG_SAVED,
	TEMP_CONFIG_SAVED,
	HUM_CONFIG_SAVED
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
	Screen(const char* l) : label(l) {}

	virtual ~Screen() = default;
	virtual EVENT_TYPE handleInput(INPUT_TYPE input) = 0;
	const char* getLabel() const { return label; }
	void render(DisplayEngine& engine);

private:
	virtual void draw(DisplayEngine& engine) const = 0;
	const char* const label;
};

class HomeScreen : public Screen {
public:
	HomeScreen() : Screen("Home") {}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	void update(const SensorRead& r) { reading = r; }

private:
	 void draw(DisplayEngine& engine) const override;
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
	 void draw(DisplayEngine& engine) const override;

	 Screen* selection = nullptr;
	 const menuArray menu;
	 uint8_t cursorPos = 0;
};

#endif

