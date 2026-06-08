#include "app.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include <stdio.h>

#define DEBOUNCE_TIME_MS 10

enum class BUTTON_STATE : uint8_t {
	IDLE,
	PRESSED_DEBOUNCING,
	PRESSED_STABLE,
	RELEASED_DEBOUNCING
};

struct Debounce_t {
    BUTTON_STATE state; 	 // debounced output
    bool rawActive;    		// last read input
    uint32_t lastRawChangeTime; // time when raw input changed
};

void debounceUpdate(Debounce_t& db);


struct Encoder_t {
    uint8_t prev_state = 0;
    int32_t position = 0;
};

const uint8_t leftTurnPath[] = {1, 3, 2, 0};
const uint8_t rightTurnPath[] = {2, 3, 1, 0};

Controller* cPtr = nullptr;
Debounce_t pushButton{};
Encoder_t enc{};

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherStation ws(sensor);
	Controller c(ws);
	cPtr = &c;
	c.init();

	while (true) {
		static uint8_t lastState = 255;

		uint8_t a = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
		uint8_t b = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);

		uint8_t state = (a << 1) | b;

		if (state != lastState) {
			static uint8_t const* currentPath = nullptr;
			static uint8_t index = 0;

			if (index == 0) {
				if (state == 1) {
					currentPath = leftTurnPath;
					++index;
				} else if (state == 2) {
					currentPath = rightTurnPath;
					++index;
				}
			} else if (state == currentPath[index]) {
				if (++index == 4) {
					enc.position = currentPath == leftTurnPath ? enc.position - 1 : enc.position + 1;
					INPUT_TYPE input = currentPath == leftTurnPath ? INPUT_TYPE::LEFT : INPUT_TYPE::RIGHT;
					c.pushInput(input);
					index = 0;
				}
			} else {
				index = 0;
			}

			printf("%li\n", enc.position);
			lastState = state;
		}



		auto startState = pushButton.state;
		debounceUpdate(pushButton);

		if (startState == BUTTON_STATE::PRESSED_DEBOUNCING && pushButton.state == BUTTON_STATE::PRESSED_STABLE) {
			c.pushInput(INPUT_TYPE::ENTER);
		}

		c.run();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_12) {
		pushButton.rawActive = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
		pushButton.lastRawChangeTime = HAL_GetTick();
	} else {

	}
}

void debounceUpdate(Debounce_t& db)
{
	uint32_t now = HAL_GetTick();

	switch (db.state) {
	case BUTTON_STATE::IDLE:
		if (db.rawActive)
			db.state = BUTTON_STATE::PRESSED_DEBOUNCING;
		break;
	case BUTTON_STATE::PRESSED_DEBOUNCING:
		if (db.rawActive && now - db.lastRawChangeTime >= DEBOUNCE_TIME_MS)
			db.state = BUTTON_STATE::PRESSED_STABLE;
		break;
	case BUTTON_STATE::PRESSED_STABLE:
		if (!db.rawActive)
			db.state = BUTTON_STATE::RELEASED_DEBOUNCING;
		break;
	case BUTTON_STATE::RELEASED_DEBOUNCING:
		if (!db.rawActive && now - db.lastRawChangeTime >= DEBOUNCE_TIME_MS)
			db.state = BUTTON_STATE::IDLE;
	}
}
