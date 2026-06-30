#ifndef UTILS_INC_OBSERVER_H_
#define UTILS_INC_OBSERVER_H_

#include "data_structs.h"
#include <array>
#include <stdint.h>

static constexpr uint8_t MAX_OBSERVERS = 5;

class WeatherObserver {
public:
	WeatherObserver() = default;
	virtual ~WeatherObserver() = default;
	virtual void onWeatherUpdate(const SensorRead& data) = 0;
};

class SettingsObserver {
public:
	SettingsObserver() = default;
	virtual ~SettingsObserver() = default;
	virtual void onSettingsChange(const Settings& settings) = 0;
};

template <typename ObserverType>
class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;

	void addObserver(ObserverType* observer) { observers.at(count++) = observer; }
	virtual void notifyObservers() const = 0;

protected:
	std::array<ObserverType*, MAX_OBSERVERS> observers{};
	uint8_t count = 0;
};



#endif /* UTILS_INC_OBSERVER_H_ */
