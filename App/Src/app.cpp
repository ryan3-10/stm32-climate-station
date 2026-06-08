#include "app.h"
#include "circular_queue.h"
#include "controller.h"
#include "sht31_sensor.h"
#include "weather_station.h"
#include <stdio.h>

constexpr uint32_t DEBOUNCE_TIME = 10;

volatile bool buttonFlag = false;
volatile bool buttonActive = false;
volatile uint32_t timestamp = 0;

CircularQueue<INPUT_TYPE, 50> inputQ;

void run_app(I2C_HandleTypeDef* hi2c) {
	Sht31Sensor sensor(hi2c);
	WeatherStation ws(sensor);
	Controller c(ws);
	c.init();

	while (true) {
		if (buttonActive && buttonFlag && HAL_GetTick() - timestamp > DEBOUNCE_TIME) {
			inputQ.push(INPUT_TYPE::ENTER);
			buttonFlag = false;
		}

		INPUT_TYPE input{};
		while (inputQ.pop(input)) {
			c.handleInput(input);
		}

		c.updateComponents();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_12) {
		buttonFlag = true;
		buttonActive = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
		timestamp = HAL_GetTick();
	} else if (GPIO_Pin == GPIO_PIN_9 || GPIO_Pin == GPIO_PIN_10) {
		static uint8_t state1 = 255;
		static uint8_t state2 = 255;

		uint8_t a = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
		uint8_t b = !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
		uint8_t state3 = (a << 1) | b;

		if (state3 != state2) {
			if (state1 == 1 && state2 == 3 && state3 == 2) {
				inputQ.push(INPUT_TYPE::LEFT);
			} else if (state1 == 2 && state2 == 3 && state3 == 1) {
				inputQ.push(INPUT_TYPE::RIGHT);
			}

			state1 = state2;
			state2 = state3;
		}
    }
}
