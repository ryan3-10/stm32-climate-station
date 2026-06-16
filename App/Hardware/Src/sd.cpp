#include "sd.h"
#include <cassert>
#include <stdio.h>
#include <stm32f4xx_hal.h>

void Sd::sendSpiCommand(uint8_t* command) {
	HAL_SPI_Transmit(spi, command, 6, HAL_MAX_DELAY);
}

uint8_t Sd::readNextValidByte() {
	constexpr uint8_t SAFETY_LIMIT = 10;
	uint8_t tx = 0xFF;
	uint8_t rx = 0xFF;

	// loop until a valid byte is received, or limit is reached
	for (uint8_t i = 0; i < SAFETY_LIMIT; ++i) {
		HAL_SPI_TransmitReceive(spi, &tx, &rx, 1, 1000);

		if (rx != 0xFF)
			break;
	}
	return rx;
}

uint8_t Sd::readNextByte() {
	uint8_t tx = 0xFF;
	uint8_t rx = 0xFF;
	HAL_SPI_TransmitReceive(spi, &tx, &rx, 1, 1000);
	return rx;
}

void Sd::select() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

void Sd::deselect() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

void Sd::init(SPI_HandleTypeDef* s) {
	spi = s;
	deselect();

	// Sent dummy data for init clock cycles
	uint8_t tx = 0xFF;
	for (uint8_t i = 0; i < 10; ++i) {
		HAL_SPI_Transmit(spi, &tx, 1, HAL_MAX_DELAY);
	}

	// select chip and send idle command
	select();
	sendSpiCommand(cmd0);

	// wait for response
	auto resp0 = readNextValidByte();
	printf("%x\n", resp0);

	// cmd8
	sendSpiCommand(cmd8);
	uint8_t r7[5];
	r7[0] = readNextValidByte();

	for (uint8_t i = 1; i < 5; ++i) {
		r7[i] = readNextByte();
	}

	for (uint8_t i = 0; i < 5; ++i) {
		printf("%x\n", r7[i]);
	}

	deselect();
}
