#include "dependency_mocks.h"
#include "system_health.h"
#include <gtest/gtest.h>
#include <string>

TEST(SystemHealthTest, OnlyHealthChecksErrorsOnUpdate) {
    HealthCheckablemock mockStatusOk{"", true};
    HealthCheckablemock mockStatusErr{"", false};
    SystemHealth sh{{&mockStatusOk, &mockStatusErr, nullptr}};
    
    // Health check error component
    sh.update();

    EXPECT_TRUE(mockStatusErr.hasBeenChecked);
    EXPECT_FALSE(mockStatusOk.hasBeenChecked);
}

TEST(SystemHealthTest, ProducesSysemOkSummaryWhenNoErrors) {
    HealthCheckablemock mock1{"", true};
    HealthCheckablemock mock2{"", true};
    HealthCheckablemock mock3{"", true};
    SystemHealth sh{{&mock1, &mock2, &mock3}};

    std::string summary = sh.getHealthSummary().data();
    EXPECT_EQ(summary, "System Ok");
}

TEST (SystemHealthTest, ProducesErrorSummaryWhenErrorsPresent) {
    HealthCheckablemock mock1{"m1", false};
    HealthCheckablemock mock2{"m2", true};
    HealthCheckablemock mock3{"m3", true};
    SystemHealth sh{{&mock1, &mock2, &mock3}};

    // With just 1 failed component
    std::string summary = sh.getHealthSummary().data();
    EXPECT_EQ(summary, "Err: m1");

    // With 2 failed components
    mock3.okFlag = false;
    summary = sh.getHealthSummary().data();
    EXPECT_EQ(summary, "Err: m1 m3");

    // With 3 failed components
    mock2.okFlag = false;
    summary = sh.getHealthSummary().data();
    EXPECT_EQ(summary, "Err: m1 m2 m3");
}

