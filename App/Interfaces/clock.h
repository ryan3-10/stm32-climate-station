#ifndef INTERFACES_CLOCK_H_
#define INTERFACES_CLOCK_H_

#include "stdint.h"

struct DateTime;

class IClock {
public:
	virtual ~IClock() = default;
	virtual bool now(DateTime& dt) = 0;
};

struct DateTime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

#endif /* INTERFACES_CLOCK_H_ */
