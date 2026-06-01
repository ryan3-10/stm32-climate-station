
#ifndef EDITABLE_H_
#define EDITABLE_H_

template <typename T>
class Cycler {
public:
	Cycler(T& start, T m)
		: dat(start)
		, MAX(m)
		, MIN(static_cast<T>(0))
	{

	}

	inline void increment() { dat = dat == MAX ? MIN : static_cast<T>(dat + 1); }
	inline void decrement() { dat = dat == MIN ? MAX : static_cast<T>(dat - 1); }
	inline T data() const { return dat; }
	inline void set(const T& d) { dat = d; }

private:
	T& dat;
	const T MAX;
	const T MIN;
};

#endif /* INC_EDITCONFIG_H_ */
