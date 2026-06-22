#ifndef HARDWARE_INC_TIME_H_
#define HARDWARE_INC_TIME_H_

#include <stm32f4xx_hal.h>
uint32_t getTick() { return HAL_GetTick(); }

#endif /* HARDWARE_INC_TIME_H_ */
