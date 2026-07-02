#ifndef HARDWARE_INC_TIME_UTIL_H_
#define HARDWARE_INC_TIME_UTIL_H_

#include <stm32f4xx_hal.h>

namespace TimeUtil {
	inline uint32_t getTick() { return HAL_GetTick(); }
	inline uint32_t timeElapsed(uint32_t time) { return HAL_GetTick() - time; }
}

#endif /* HARDWARE_INC_TIME_H_ */
