#ifndef INTERFACES_CLOCK_H_
#define INTERFACES_CLOCK_H_

#include "date_time.h"
#include <stdint.h>

class IClock {
public:
	virtual ~IClock() = default;
	virtual bool now(DateTime::Model& dt) = 0;
};

#endif /* INTERFACES_CLOCK_H_ */
