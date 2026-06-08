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

const uint8_t leftTurnPath[] = {1, 3, 2};
const uint8_t altLeftTurnPath[] = {3, 2, 0};
const uint8_t rightTurnPath[] = {2, 3, 1};

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
	} else if (GPIO_Pin == GPIO_PIN_9 || GPIO_Pin == GPIO_PIN_10) {
		static uint8_t state1 = 255;
		static uint8_t state2 = 255;

		uint8_t a = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
		uint8_t b = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
		uint8_t state3 = (a << 1) | b;

		if (state3 != state2) {
			if (state1 == 1 && state2 == 3 && state3 == 2) {
				cPtr->pushInput(INPUT_TYPE::LEFT);
			} else if (state1 == 2 && state2 == 3 && state3 == 1) {
				cPtr->pushInput(INPUT_TYPE::RIGHT);
			}

			state1 = state2;
			state2 = state3;
		}
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
