cmake_minimum_required(VERSION 3.28)
project(lab_4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_4
        tests/gameEngineTests.cpp
        #src/main.cpp
        src/engine/Field.h
        src/engine/Field.cpp
        src/engine/Snake.h
        src/engine/Snake.cpp
        src/engine/FoodDistributor.h
        src/engine/FoodDistributor.cpp
        src/engine/MoveStrategies.h
        src/engine/StepStrategyStd.h
        src/engine/StepStrategyStd.cpp
        src/engine/EatStrategyStd.h
        src/engine/EatStrategyStd.cpp
        src/engine/KillStrategyStd.h
        src/engine/KillStrategyStd.cpp
        src/engine/BornStrategyStd.h
        src/engine/BornStrategyStd.cpp
        src/engine/FindPlaceStrategyStd.h
        src/engine/FindPlaceStrategyStd.cpp
        src/engine/Commands.h
        src/engine/Commands.cpp
        src/engine/CommandExecutor.h
        src/engine/CommandExecutor.cpp
        src/engine/CommandsQueue.h
        src/engine/CommandsQueue.cpp
        src/engine/Player.h
        src/engine/Player.cpp
        src/snakes.pb.h
        src/snakes.pb.cc
        src/net/MulticastReceiver.cpp
        src/net/MulticastReceiver.h
        src/net/UDPNetworkEnd.cpp
        src/net/UDPNetworkEnd.h
        src/net/ConnectionsList.cpp
        src/net/ConnectionsList.h
        src/model/FieldState.cpp
        src/model/FieldState.h
        src/model/PlayersListState.h
        src/model/PlayersListState.cpp
        src/model/PlayersListState.h
        src/model/GamesListState.cpp
        src/model/GamesListState.h
        src/net/ViewerState.cpp
        src/net/ViewerState.h
        src/net/NormalState.cpp
        src/net/NormalState.h
        src/net/DeputyState.cpp
        src/net/DeputyState.h
        src/net/MasterState.cpp
        src/net/MasterState.h
        src/engine/Launcher.cpp
        src/engine/Launcher.h
        src/engine/ConfigReader.cpp
        src/engine/ConfigReader.h
        src/engine/PlayersList.cpp
        src/engine/PlayersList.h
        src/net/NetMember.cpp
        src/net/NetMemberState.cpp
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

find_package(Protobuf REQUIRED)
#include_directories(${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(lab_4 PUBLIC ${PROTOBUF_LIBRARIES})

