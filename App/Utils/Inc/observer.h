#ifndef UTILS_INC_OBSERVER_H_
#define UTILS_INC_OBSERVER_H_

#include "data_structs.h"
#include <array>
#include <stdint.h>

namespace {
	constexpr uint8_t MAX_OBSERVERS = 5;
}

class WeatherObserver {
public:
	WeatherObserver() = default;
	virtual ~WeatherObserver() = default;
	virtual void onWeatherUpdate(const WeatherData& data) = 0;
};

class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;

	void addObserver(WeatherObserver* observer) { observers.at(count++) = observer; }
	virtual void notifyObservers() const = 0;

protected:
	std::array<WeatherObserver*, MAX_OBSERVERS> observers;
	uint8_t count = 0;
};



#endif /* UTILS_INC_OBSERVER_H_ */
