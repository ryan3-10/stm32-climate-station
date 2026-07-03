#ifndef UI_INC_CONFIG_SCREEN_H_
#define UI_INC_CONFIG_SCREEN_H_

#include "screen.h"
#include "ui_models.h"

class ConfigScreen : public Screen {
	static constexpr uint8_t NUM_ITEMS = 3;

public:
	ConfigScreen(const ConfigScreenLayout& lay, EVENT_TYPE event)
		: Screen(lay.header)
		, layout(lay)
		, onSave(event)
	{}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;
	ConfigEdit getConfigEdit() { return config; }

private:
	void drawBody(DisplayEngine& engine) const override;
	void stepUp();
	void stepDown();

	const ConfigScreenLayout layout;
	ConfigEdit config;
	uint8_t cursorPos = 0;
	EVENT_TYPE onSave;
};

ConfigScreenLayout LogLayout();
ConfigScreenLayout TempAlertLayout();
ConfigScreenLayout HumAlertLayout();

#endif /* UI_INC_CONFIG_SCREEN_H_ */
