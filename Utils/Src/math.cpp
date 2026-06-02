#include "math.h"

uint32_t hoursToMili(uint32_t hours) {
	return hours * 60 * 60 * 1000;
}

uint32_t minToMili(uint32_t minutes) {
	return minutes * 60 * 1000;
}

