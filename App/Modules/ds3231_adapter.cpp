#include "ds3231_adapter.h"

#include "ds3231.h"

void Ds3231Adapter::runHealthCheck() {
	uint8_t dummy[7];
	ds3231.currentDateTime(dummy);
}

bool Ds3231Adapter::now(DateTime& dt) {
	return ds3231.currentDateTime(&dt.second) == Ds3231::Status::Ok;
}
