#ifndef HARDWARE_INC_TIME_UTIL_H_
#define HARDWARE_INC_TIME_UTIL_H_

#include <stm32f4xx_hal.h>

namespace Utils {
	inline uint32_t getTick() { return HAL_GetTick(); }
	inline uint32_t timeElapsed(uint32_t time) { return HAL_GetTick() - time; }
	inline uint32_t hoursToMili(uint32_t hours) { return hours * 60 * 60 * 1000; }
	inline uint32_t minToMili(uint32_t minutes) { return minutes * 60 * 1000; }
}

#endif /* HARDWARE_INC_TIME_H_ */
