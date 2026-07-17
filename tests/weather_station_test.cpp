#include "dependency_mocks.h"
#include "weather_station.h"
#include <gtest/gtest.h>

TEST(WeatherStationTest, NotifiesOnSignificantWeatherChanges) {
    WeatherSensorMock sensorMock;
    sensorMock.data = {0.0f, 0.0f};
    WeatherStation ws{sensorMock};
    ws.init();
    ObserverMock obsMock;
    ws.addObserver(&obsMock);

    // Change temperature by more than +threshold and update station
    // should notify observer
    sensorMock.data.temp += 0.31f;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);
    
    // Reset obsMock
    obsMock.hasBeenNotified = false;

    // Change humidity by more than +threshold and update station 
    // should notify observer
    sensorMock.data.hum += 0.31f;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);

    // Now test the same thing, but subtracting by 0.31 instead of adding
    
    // Reset sensorMock
    sensorMock.data = {100.0f, 100.0f};
    ws.update();

    // Reset obsMock
    obsMock.hasBeenNotified = false;

    // Change temperature by more than -threshold and update station
    // should notify observer
    sensorMock.data.temp -= 0.31f;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);

    // Reset obsMock
    obsMock.hasBeenNotified = false;

    // Change humidity by more than -threshold and update station 
    // should notify observer
    sensorMock.data.hum -= 0.31f;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);
}

TEST(WeatherStationTest, IgnoresInsignificantWeatherChanges) {
    WeatherSensorMock sensorMock;
    sensorMock.data = {59.6f, 59.6f};
    WeatherStation ws{sensorMock};
    ws.init();
    ObserverMock obsMock;
    ws.addObserver(&obsMock);

    // Add threshold to temp and update station - should not notify
    sensorMock.data.temp += 0.29;
    ws.update();
    ASSERT_FALSE(obsMock.hasBeenNotified);

    // Add threshold to hum and update station - should not notify
    sensorMock.data.hum += 0.29;
    ws.update();
    ASSERT_FALSE(obsMock.hasBeenNotified);

    // Now setting temp to 0.29 less than the last significant reading
    // Still should not notify
    sensorMock.data.temp -= 0.58;
    ws.update();
    ASSERT_FALSE(obsMock.hasBeenNotified);

    // Now setting hum to 0.29 less than the last significant reading
    // Still should not notify
    sensorMock.data.hum -= 0.58;
    ws.update();
    ASSERT_FALSE(obsMock.hasBeenNotified);
}

TEST(WeatherStationTest, RespectsStatusOfReads) {
    WeatherSensorMock sensorMock;
    sensorMock.statusOk = false;
    WeatherStation ws{sensorMock};
    ws.init();
    ObserverMock obsMock;
    ws.addObserver(&obsMock);

    sensorMock.data = {999, 999};

    // Since statusOk is still false, station should not notify
    ws.update();
    ASSERT_FALSE(obsMock.hasBeenNotified);

    // When statusOk becomes true, station should notify
    sensorMock.statusOk = true;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);

    obsMock.hasBeenNotified = false;

    // When statusOk becomes false again, station should notify
    sensorMock.statusOk = false;
    ws.update();
    EXPECT_TRUE(obsMock.hasBeenNotified);
}