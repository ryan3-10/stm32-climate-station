#include "rotary_encoder.h"
#include <atomic>
#include <stdint.h>
#include <stm32f4xx_hal.h>

namespace {
	#define ENCODER_PORT GPIOD
	constexpr uint32_t DEBOUNCE_TIME = 10;
	constexpr uint16_t ENCODER_BUTTON_PIN = GPIO_PIN_12;
	constexpr uint16_t ENCODER_A_PIN = GPIO_PIN_9;
	constexpr uint16_t ENCODER_B_PIN = GPIO_PIN_10;

	std::atomic<bool> g_buttonFlag = false;
	std::atomic<int32_t> g_encoderPos = 0;
	volatile uint32_t g_timestamp = 0;
}

int32_t RotaryEncoder::readPos() const {
	// return the value of the global position and reset it to 0
	return g_encoderPos.exchange(0);
}

bool RotaryEncoder::buttonWasPressed() const {
	auto now = HAL_GetTick();
	bool pressed = false;

	if (g_buttonFlag && now - g_timestamp > DEBOUNCE_TIME) {
		// buttonFlag may have been set from a release debounce, so read current pin state
		pressed = HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_BUTTON_PIN);
		g_buttonFlag = false;
	}

	return pressed;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == ENCODER_BUTTON_PIN) {
		g_buttonFlag = true;
		g_timestamp = HAL_GetTick();
	} else if (GPIO_Pin == ENCODER_A_PIN || GPIO_Pin == ENCODER_B_PIN) {
		static uint8_t state1 = 255;
		static uint8_t state2 = 255;

		uint8_t a = !HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_A_PIN);
		uint8_t b = !HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_B_PIN);
		uint8_t state3 = (a << 1) | b;

		if (state3 != state2) {
			if (state1 == 1 && state2 == 3 && state3 == 2) {
				--g_encoderPos;
			} else if (state1 == 2 && state2 == 3 && state3 == 1) {
				++g_encoderPos;
			}

			state1 = state2;
			state2 = state3;
		}
    }
}



