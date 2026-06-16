#include <stm32f4xx_hal.h>

#ifndef HARDWARE_INC_SD_H_
#define HARDWARE_INC_SD_H_

class Sd {
public:
	Sd() = default;
	void init(SPI_HandleTypeDef* s);

private:
	void sendSpiCommand(uint8_t* command);
	uint8_t readNextValidByte();
	uint8_t readNextByte();
	void goIdle();
	void select();
	void deselect();

	SPI_HandleTypeDef* spi;

	// commands
	uint8_t cmd0[6] = { 0x40, 0x00, 0x00, 0x00, 0x00, 0x95}; 	// GO_IDLE
	uint8_t cmd8[6] = { 0x48, 0x00, 0x00, 0x01, 0xAA, 0x87 }; 	// SEND_IF_COND
};



#endif /* HARDWARE_INC_SD_H_ */
