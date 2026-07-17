#include "clock.h"
#include "health_checkable.h"
#include "observer.h"
#include "weather_sensor.h"
#include <string>

class ClockMock : public IClock {
public:    
    bool now(DateTime::Model& dt) override {
        dt = dateTime;
        return statusOk;
    }

    DateTime::Model dateTime{};
    bool statusOk = true;
};

class FileWriterMock {
public:
    void writeToFile(const char* fileName, const char* text) {
        lastFileWrittenTo = fileName;
        lastWrittenString = text;
    }

    std::string lastFileWrittenTo = "";
    std::string lastWrittenString = "";
};

class HealthCheckablemock : public IHealthCheckable {
public:
    HealthCheckablemock(const std::string& err, bool startingOkFlag)
        : errorCode(err)
        , okFlag(startingOkFlag)
    {}

    const char* getErrorCode() const override {
        return errorCode.data();
    }

    bool isOk() const override {
        return okFlag;
    }

    void runHealthCheck() override {
        hasBeenChecked = true;
    }

    std::string errorCode;
    bool okFlag;
    bool hasBeenChecked = false;
};

class ObserverMock : public Observer {
public:
    void onWeatherUpdate(const SensorRead& data) override {
        hasBeenNotified = true;
    }

    bool hasBeenNotified = false;
};

class WeatherSensorMock : public IWeatherSensor {
public:
    bool getWeather(WeatherData& wd) override {
        wd = data;
        return statusOk;
    }

    bool statusOk = true;
    WeatherData data{};
};