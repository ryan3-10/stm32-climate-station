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
	virtual EVENT_TYPE handleInput(INPUT_TYPE input) = 0;
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
	HomeScreen() : Screen("Home") {}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	void update(float t, float h, bool ok) { temp = t; hum = h; statusOk = ok; }

private:
	 void draw() const override;
	 float temp;
	 float hum;
	 bool statusOk;
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
	ConfigScreen(const ConfigScreenLayout& lay) : Screen(lay.header), layout(lay)
	{}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	void getEdits(uint16_t& data1, uint16_t& data2, bool& e) const;
	void setEdits(uint16_t data1, uint16_t data2, bool e);

private:
	 void draw() const override;
	 void stepUp();
	 void stepDown();

	 const ConfigScreenLayout layout;
	 uint16_t d1 = 0;
	 uint16_t d2 = 0;
	 bool en = false;
	 uint8_t cursorPos = 0;
};

#endif

