#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <array>
#include <stdint.h>

namespace {
	constexpr uint8_t ARRAY_SIZE = 3;
}

class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void update() = 0;
};

class Subject {
private:
	std::array<Observer*, ARRAY_SIZE> observers;
	uint8_t observerCount = 0;

public:
	Subject() = default;
	virtual ~Subject() = default;

	void subscribe(Observer* observer);
	virtual void notify();
};




#endif /* INC_OBSERVER_H_ */
