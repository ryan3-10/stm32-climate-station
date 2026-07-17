#ifndef TESTS_MOCKS_HARDWARE_UTILS_H_
#define TESTS_MOCKS_HARDWARE_UTILS_H_

#include <stdint.h>

namespace HardwareUtils {
    inline uint32_t getTick() { return UINT32_MAX; }
    inline uint32_t timeElapsed(uint32_t) { return UINT32_MAX; }
}

#endif