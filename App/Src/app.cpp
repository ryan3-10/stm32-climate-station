#include "app.h"
#include "circular_queue.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include <stdio.h>

constexpr uint32_t DEBOUNCE_TIME = 10;

volatile bool buttonFlag = false;
volatile uint32_t timestamp = 0;
volatile int32_t encoderPos = 0;


void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherStation ws(sensor);
	Controller c(ws);
	c.init();

	while (true) {
		auto now = HAL_GetTick();

		if (buttonFlag && now - timestamp > DEBOUNCE_TIME) {
			c.handleInput(INPUT_TYPE::ENTER);
			buttonFlag = false;
		}

		if (encoderPos != 0) {
			int8_t increment = encoderPos > 0 ? -1 : +1;
			INPUT_TYPE input = encoderPos > 0 ? INPUT_TYPE::RIGHT : INPUT_TYPE::LEFT;
			while (encoderPos != 0) {
				c.handleInput(input);
				encoderPos += increment;
			}
		}

		c.updateComponents();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_12) {
		buttonFlag = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
		timestamp = HAL_GetTick();
	} else if (GPIO_Pin == GPIO_PIN_9 || GPIO_Pin == GPIO_PIN_10) {
		static uint8_t state1 = 255;
		static uint8_t state2 = 255;

		uint8_t a = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
		uint8_t b = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
		uint8_t state3 = (a << 1) | b;

		if (state3 != state2) {
			if (state1 == 1 && state2 == 3 && state3 == 2) {
				--encoderPos;
			} else if (state1 == 2 && state2 == 3 && state3 == 1) {
				++encoderPos;
			}

			state1 = state2;
			state2 = state3;
		}
    }
}
