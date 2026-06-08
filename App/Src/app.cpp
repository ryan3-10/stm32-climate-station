#include "app.h"
#include "circular_queue.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include <atomic>
#include <stdio.h>

constexpr uint32_t DEBOUNCE_TIME = 10;

std::atomic<bool> g_buttonFlag = false;
std::atomic<int32_t> g_encoderPos = 0;
volatile uint32_t g_timestamp = 0;

// Allocate long-lived objects statically to protect the stack
static Sht31Sensor sensor;
static WeatherStation ws(sensor);
static Controller c(ws);

void run_app(I2C_HandleTypeDef* hi2c) {
	// Late bind hardware
	sensor.init(hi2c);
	c.init();

	while (true) {
		auto now = HAL_GetTick();

		// Handle push button input
		if (g_buttonFlag && now - g_timestamp > DEBOUNCE_TIME && HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12)) {
			c.handleInput(INPUT_TYPE::ENTER);
			g_buttonFlag = false;
		}

		// Handle rotary click inputs
		auto localEncoderPos = g_encoderPos.exchange(0); // get a snapshot of g_encoderPos, and set it to 0
		if (localEncoderPos != 0) {
			INPUT_TYPE input = localEncoderPos > 0 ? INPUT_TYPE::RIGHT : INPUT_TYPE::LEFT;

			for (int32_t i = 0; i < std::abs(localEncoderPos); ++i) {
				c.handleInput(input);
			}
		}

		// Update controller's components
		c.updateComponents();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_12) {
		g_buttonFlag = true;
		g_timestamp = HAL_GetTick();
	} else if (GPIO_Pin == GPIO_PIN_9 || GPIO_Pin == GPIO_PIN_10) {
		static uint8_t state1 = 255;
		static uint8_t state2 = 255;

		uint8_t a = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
		uint8_t b = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
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
