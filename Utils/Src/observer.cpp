#ifndef SRC_OBSERVER_CPP_
#define SRC_OBSERVER_CPP_

#include <observer.h>
#include <cassert>
#include <stdint.h>

void Subject::subscribe(Observer* observer) {
	// Uses bounds checking
	observers.at(observerCount++) = observer;
}

#endif /* SRC_OBSERVER_CPP_ */
