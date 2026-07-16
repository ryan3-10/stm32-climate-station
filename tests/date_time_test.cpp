#include "date_time.h"
#include <gtest/gtest.h>

TEST(DateTimeTest, EpochSeconds) {
    // Test toEpochSeconds with Epoch model
    DateTime dt1({0, 0, 0, 6, 1, 1, 0});
    EXPECT_EQ(dt1.toEpochSeconds(), 0);

    // Test going from DateTime to epoch seconds back to DateTime
    dt1.setData({56, 34, 12, 3, 23, 10, 23});
    auto seconds = dt1.toEpochSeconds();
    auto dt2 = dt1.fromEpochSeconds(seconds);

    EXPECT_EQ(dt1, dt2);
}

TEST(DateTimeTest, FebruaryConversion) {
    DateTime dt({0, 0, 0, 1, 1, 2, 0});

    EXPECT_EQ(dt.toEpochSeconds(), 2678400u);
    EXPECT_EQ(dt.fromEpochSeconds(dt.toEpochSeconds()), dt);
}

TEST(DateTimeTest, EqualTo) {
    DateTime::Model model {};
    auto modelCopy = model;

    // Test with equal models
    DateTime dt1{model};
    DateTime dt2{modelCopy};
    EXPECT_TRUE(dt1 == dt2);

    // Test with 1 second off
    modelCopy.second += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);

    // Test with one minute off
    modelCopy = model;
    modelCopy.minute += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);

    // Test with one hour off
    modelCopy = model;
    modelCopy.hour += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);

    // Test with one date off
    modelCopy = model;
    modelCopy.date += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);

    // Test with one month off
    modelCopy = model;
    modelCopy.month += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);

    // Test with one year off
    modelCopy = model;
    modelCopy.year += 1;
    dt2.setData(modelCopy);
    EXPECT_FALSE(dt1 == dt2);
}

TEST(DateTimeTest, GreaterThan) {
    DateTime::Model model {};
    auto modelCopy = model;

    // Test with equal models
    DateTime dt1{model};
    DateTime dt2{modelCopy};
    EXPECT_FALSE(dt1 > dt2 || dt2 > dt1);

    // Test with 1 second off
    modelCopy.second += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);

    // Test with one minute off
    modelCopy = model;
    modelCopy.minute += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);

    // Test with one hour off
    modelCopy = model;
    modelCopy.hour += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);

    // Test with one date off
    modelCopy = model;
    modelCopy.date += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);

    // Test with one month off
    modelCopy = model;
    modelCopy.month += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);

    // Test with one year off
    modelCopy = model;
    modelCopy.year += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt2 > dt1);
}

TEST(DateTimeTest, LessThan) {
    DateTime::Model model {};
    auto modelCopy = model;

    // Test with equal models
    DateTime dt1{model};
    DateTime dt2{modelCopy};
    EXPECT_FALSE(dt1 < dt2 || dt2 < dt1);

    // Test with 1 second off
    modelCopy.second += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);

    // Test with one minute off
    modelCopy = model;
    modelCopy.minute += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);

    // Test with one hour off
    modelCopy = model;
    modelCopy.hour += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);

    // Test with one date off
    modelCopy = model;
    modelCopy.date += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);

    // Test with one month off
    modelCopy = model;
    modelCopy.month += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);

    // Test with one year off
    modelCopy = model;
    modelCopy.year += 1;
    dt2.setData(modelCopy);
    EXPECT_TRUE(dt1 < dt2);
}

TEST(DateTimeTest, Addition) {
    DateTime::Model model {0, 0, 0, 6, 1, 1, 0};
    DateTime dt1{model};

    // Add one second
    dt1 = dt1 + 1;
    model.second += 1;
    DateTime dt2{model};
    ASSERT_EQ(dt1, dt2);

    // Adding seconds that carry over to the next minute
    model.second = 30;
    dt1.setData(model);
    dt1 = dt1 + 30;
    model.second = 0;
    model.minute = 1;
    dt2.setData(model);
    ASSERT_EQ(dt1, dt2);

    // Adding seconds that carry over to the next day
    model.second = 0;
    model.minute = 59;
    model.hour = 23;
    dt1.setData(model);
    dt1 = dt1 + 60;
    model.second = 0;
    model.minute = 0;
    model.hour = 0;
    model.date = 2;
    model.day = 7;
    dt2.setData(model);
    ASSERT_EQ(dt1, dt2);

    // Adding seconds that carry over to the next year
    model.second = 0;
    model.minute = 57;
    model.hour = 23;
    model.date = 31;
    model.month = 12;
    dt1.setData(model);
    dt1 = dt1 + 180;
    model.minute = 0;
    model.hour = 0;
    model.date = 1;
    model.month = 1;
    model.day = 1;
    model.year = 1;
    dt2.setData(model);
    ASSERT_EQ(dt1, dt2);
}
