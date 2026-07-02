#ifndef INTERFACES_HEALTH_CHECKABLE_H_
#define INTERFACES_HEALTH_CHECKABLE_H_

class IHealthCheckable {
public:
	virtual ~IHealthCheckable() = default;
	virtual const char* getErrorCode() const = 0;
	virtual bool isOk() const = 0;
	virtual void runHealthCheck() = 0;
};

#endif /* INTERFACES_HEALTH_CHECKABLE_H_ */
