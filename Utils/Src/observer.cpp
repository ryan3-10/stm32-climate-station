#ifndef SRC_OBSERVER_CPP_
#define SRC_OBSERVER_CPP_

#include "observer.h"
#include "data_structs.h"
#include <cassert>
#include <stdint.h>

void Subject::addObserver(Observer* observer) {
	assert(count < MAX_OBSERVERS);

	// Uses bounds checking
	observers.at(count++) = observer;
}

void Subject::notify(const WeatherData& data) {
	for (uint8_t i = 0; i < count; ++i) {
		observers.at(i)->update(data);
	}
}

#endif /* SRC_OBSERVER_CPP_ */
