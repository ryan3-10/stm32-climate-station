#include "ds3231_clock.h"
#include "ds3231.h"

void Ds3231Clock::runHealthCheck() {
	uint8_t dummy[7];
	ds3231.currentDateTime(dummy);
}

bool Ds3231Clock::now(DateTime& dt) {
	return ds3231.currentDateTime(&dt.second) == Ds3231::Status::Ok;
}
