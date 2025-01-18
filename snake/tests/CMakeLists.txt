cmake_minimum_required(VERSION 3.30)
project(snakeTests)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(snakeTests
        engine/FieldTests.cpp
        engine/SnakeTests.cpp
        engine/FoodDistributorTests.cpp
        engine/StepStrategyTests.cpp
        engine/EatStrategyTests.cpp
        engine/KillStrategyTests.cpp
        engine/FindPlaceStrategyTests.cpp
        engine/BornStrategyTests.cpp
        engine/PlayersListTests.cpp
)

target_link_libraries(snakeTests PRIVATE GTest::GTest engine proto)

add_test(snakeGTests snakeTests)

