#ifndef UI_INC_CONFIG_SCREEN_H_
#define UI_INC_CONFIG_SCREEN_H_

#include "screen.h"

class ConfigScreen : public Screen {
	static constexpr uint8_t NUM_ITEMS = 3;

public:
	ConfigScreen(const ConfigScreenLayout& lay, EVENT_TYPE event)
		: Screen(lay.header)
		, layout(lay)
		, onSave(event)
	{}

	EVENT_TYPE handleInput(INPUT_TYPE input) override;

	template <typename Callback>
	void submitChanges(Callback callback) { callback(d1, d2, en); }

private:
	 void draw(DisplayEngine& engine) const override;
	 void stepUp();
	 void stepDown();

	 const ConfigScreenLayout layout;
	 uint16_t d1 = 0;
	 uint16_t d2 = 0;
	 bool en = false;
	 uint8_t cursorPos = 0;
	 EVENT_TYPE onSave;
};

ConfigScreenLayout LogLayout();
ConfigScreenLayout TempAlertLayout();
ConfigScreenLayout HumAlertLayout();

#endif /* UI_INC_CONFIG_SCREEN_H_ */
