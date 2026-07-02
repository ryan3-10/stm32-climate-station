#ifndef ADAPTERS_DS3231_ADAPTER_H_
#define ADAPTERS_DS3231_ADAPTER_H_

#include "clock.h"
#include "ds3231_clock.h"
#include "health_checkable.h"

class Ds3231Adapter : public IClock, public IHealthCheckable {
public:
	Ds3231Adapter(Ds3231Clock& d) : ds3231(d) {}
	const char* getErrorCode() const override { return "Cl"; }
	bool isOk() const override { return ds3231.getStatus() == Ds3231Clock::Status::Ok; }
	void runHealthCheck() override;
	bool now(DateTime& dt) override;

private:
	Ds3231Clock& ds3231;

};

#endif /* ADAPTERS_DS3231_ADAPTER_H_ */
