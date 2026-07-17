#include "clock.h"
#include "logger.h"
#include <gtest/gtest.h>
#include <string.h>

class ClockMock : public IClock {
public:    
    bool now(DateTime::Model& dt) override {
        dt = dateTime;
        return true;
    }

    DateTime::Model dateTime;
};

class FileWriterMock {
public:
    void writeToFile(const char* fileName, const char* text) {
        lastFileWrittenTo = fileName;
        lastWrittenString = text;
    }

    std::string lastFileWrittenTo;
    std::string lastWrittenString;
};

namespace {
    ClockMock clockMock;
    FileWriterMock fwMock;
}

TEST(LoggerTest, Test) {
    Logger logger{clockMock, fwMock};
    logger.update();
    EXPECT_TRUE(true);
}