cmake_minimum_required(VERSION 3.14)

set(This WeatherStationTests)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

add_executable(tests
    tests/date_time_test.cpp
    App/Models/date_time.cpp
    tests/logger_test.cpp
    App/Services/logger.h
    App/Utils/utils.cpp
)

target_link_libraries(tests gtest gtest_main)

target_include_directories(tests PRIVATE
    App/Models
    App/Interfaces
    App/Services
    tests/Mocks
    App/Utils
)

gtest_discover_tests(tests)