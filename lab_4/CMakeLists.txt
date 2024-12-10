cmake_minimum_required(VERSION 3.28)
project(lab_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_4
        tests/gameEngineTests.cpp
        #src/main.cpp
        src/Field.h
        src/Field.cpp
        src/Snake.h
        src/Snake.cpp
        src/FoodDistributor.h
        src/FoodDistributor.cpp
        src/MoveStrategies.h
        src/StepStrategyStd.h
        src/StepStrategyStd.cpp
        src/EatStrategyStd.h
        src/EatStrategyStd.cpp
        src/KillStrategyStd.h
        src/KillStrategyStd.cpp
        src/BornStrategyStd.h
        src/BornStrategyStd.cpp
        src/FindPlaceStrategyStd.h
        src/FindPlaceStrategyStd.cpp
        src/Commands.h
        src/Commands.cpp
        src/CommandExecutor.h
        src/CommandExecutor.cpp
        src/CommandsQueue.h
        src/CommandsQueue.cpp
        src/Player.h
        src/Player.cpp
        #src/NetMember.cpp
        #src/NetMember.h
        #src/NetMemberState.h
)

target_include_directories(lab_4 PUBLIC src)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(lab_4 PUBLIC gtest_main)

#find_package(Protobuf REQUIRED)
#include_directories(${PROTOBUF_INCLUDE_DIRS})
#target_link_libraries(lab_4 PUBLIC ${PROTOBUF_LIBRARIES})

