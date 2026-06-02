#ifndef INC_CIRCULAR_QUEUE_H_
#define INC_CIRCULAR_QUEUE_H_

#include <array>
#include <cassert>
#include <stdint.h>

template <typename T, uint16_t MAX_LENGTH>
class CircularQueue {

public:
	bool push(const T& in) {
		if (isFull()) {
			return false;
		}

		data[head] = in;
		head = (head + 1) % MAX_LENGTH;
		++count;
		return true;
	}

	bool pop(T& out) {
		if (isEmpty()) {
			return false;
		}

		out = data[tail];
		tail = (tail + 1) % MAX_LENGTH;
		--count;
		return true;
	}

	bool isEmpty() const {
		return count == 0;
	}

	bool isFull() const {
		return count == MAX_LENGTH;
	}

private:
	uint16_t count = 0;
	uint16_t head = 0;
	uint8_t tail = 0;
	std::array<T, MAX_LENGTH> data;
};



#endif /* INC_CIRCULAR_QUEUE_H_ */
