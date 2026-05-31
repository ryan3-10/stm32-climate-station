#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "data_structs.h"
#include <array>
#include <stdint.h>


class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void update(const WeatherData& data) = 0;
};

class Subject {
private:
	static constexpr uint8_t MAX_OBSERVERS = 3;
	std::array<Observer*, MAX_OBSERVERS> observers;
	uint8_t count = 0;

public:
	Subject() = default;
	virtual ~Subject() = default;

	void addObserver(Observer* observer);
	virtual void notify(const WeatherData& data);
};




#endif /* INC_OBSERVER_H_ */
