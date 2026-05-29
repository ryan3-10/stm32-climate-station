#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <array>
#include <stdint.h>

namespace {
	constexpr uint8_t ARRAY_SIZE = 3;
}

enum class STATUS_CODE : uint8_t {
	OK,
	ERROR
};

class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void update(float temp, float hum, bool statusOk) = 0;
};

class Subject {
protected:
	std::array<Observer*, ARRAY_SIZE> observers;
	uint8_t observerCount = 0;

public:
	Subject() = default;
	virtual ~Subject() = default;

	void subscribe(Observer* observer);
	virtual void notify() = 0;
};




#endif /* INC_OBSERVER_H_ */
