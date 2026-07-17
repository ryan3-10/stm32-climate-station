#ifndef UTILS_HARDWARE_UTILS_H_
#define UTILS_HARDWARE_UTILS_H_

#include <stdint.h>
#include <stm32f4xx_hal.h>

namespace HardwareUtils {
    inline uint32_t getTick() { return HAL_GetTick(); }
	inline uint32_t timeElapsed(uint32_t time) { return HAL_GetTick() - time; }
}

#endif
