#include "clock.h"
#include "logger.h"
#include <gtest/gtest.h>
#include <string.h>

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

TEST(LoggerTest, DoesNotLogWhenDisabled) {
    ClockMock clockMock;
    FileWriterMock fwMock;
    Logger logger{clockMock, fwMock};
    logger.setConfig({0, 0, false});
    
    // Should not log anything
    logger.update();
    EXPECT_EQ(fwMock.lastWrittenString, "");

    logger.setConfig({10, 3, false});
    // Still no log expected
    logger.update();
    EXPECT_EQ(fwMock.lastWrittenString, "");
}

TEST(LoggerTest, LogsSensorDataWhenClockIsError) {
    ClockMock clockMock;
    FileWriterMock fwMock;
    SensorRead sampleRead {
        .data{50.0f, 100.0f},
        .statusOk = true
    };

    // Test logging with a clock error but a good sensor read
    Logger logger{clockMock, fwMock};
    logger.setConfig({0, 0, true});
    clockMock.statusOk = false;
    logger.onWeatherUpdate(sampleRead);
    logger.update();
    std::string expectedLog = "Clock Error - Temp: 50.0F Humidity: 100.0%\n";
    EXPECT_EQ(fwMock.lastFileWrittenTo, "log.txt");
    EXPECT_EQ(fwMock.lastWrittenString, expectedLog);

    // Change weather data and log again
    sampleRead.data = {95.3f, 45.8f};
    logger.onWeatherUpdate(sampleRead);
    logger.update();
    expectedLog = "Clock Error - Temp: 95.3F Humidity: 45.8%\n";
    EXPECT_EQ(fwMock.lastWrittenString, expectedLog);
}

TEST(LoggerTest, LogsClockDataWhenSensorIsError) {
    ClockMock clockMock;
    FileWriterMock fwMock;
    SensorRead sampleRead { .statusOk = false };

    // Test logging with good clock data but a sensor error
    Logger logger{clockMock, fwMock};
    logger.setConfig({1, 1, true});
    clockMock.dateTime = {0, 0, 0, 1, 1, 1, 0};
    logger.onWeatherUpdate(sampleRead);
    logger.update();
    std::string expectedLog = "01/01/00 00:00:00 - Sensor Error\n";
    EXPECT_EQ(fwMock.lastWrittenString, expectedLog);

    // Change clock data and test again
    clockMock.dateTime = {0, 29, 19, 1, 16, 7, 26};
    logger.update();
    expectedLog = "07/16/26 19:29:00 - Sensor Error\n";
    EXPECT_EQ(fwMock.lastWrittenString, expectedLog);
}

TEST(LoggerTest, LogsOnlyAfterConfiguredInterval) {
    ClockMock clockMock;
    FileWriterMock fwMock;
    Logger logger(clockMock, fwMock);

    // Set clockMock to an easy starting state
    clockMock.dateTime.second = 0;
    clockMock.dateTime.minute = 0;
    clockMock.dateTime.hour = 0;

    // Set interval for 10 minutes
    logger.setConfig({0, 10, true});

    // With logging now enabled, logger should write initial
    // log on next update
    logger.update();
    EXPECT_EQ(fwMock.lastFileWrittenTo, "log.txt");

    // Reset fwMock
    fwMock.lastFileWrittenTo = "";
    fwMock.lastWrittenString = "";

    // "Wait" 9 and 59 seconds
    clockMock.dateTime.minute = 9;
    clockMock.dateTime.second = 59;

    // Logger should not log yet
    logger.update();
    EXPECT_EQ(fwMock.lastFileWrittenTo, "");

    // "Wait" one more second
    clockMock.dateTime.minute = 10;
    clockMock.dateTime.second = 0;

    // Logger should log now
    logger.update();
    EXPECT_EQ(fwMock.lastFileWrittenTo, "log.txt");
}