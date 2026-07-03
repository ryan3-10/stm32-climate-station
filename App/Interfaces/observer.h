#ifndef UTILS_INC_OBSERVER_H_
#define UTILS_INC_OBSERVER_H_

#include "config_models.h"
#include "weather_models.h"
#include <array>
#include <stdint.h>

static constexpr uint8_t MAX_OBSERVERS = 5;

class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void onWeatherUpdate(const SensorRead& data) = 0;
};

class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;

	void addObserver(Observer* observer) { observers.at(count++) = observer; }
	virtual void notifyObservers() const = 0;

protected:
	std::array<Observer*, MAX_OBSERVERS> observers{};
	uint8_t count = 0;
};



#endif /* UTILS_INC_OBSERVER_H_ */
