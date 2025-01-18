project(engine)

add_library(engine
        Field.h Field.cpp
        Snake.h Snake.cpp
        FoodDistributor.h FoodDistributor.cpp
        MoveStrategies.h
        StepStrategyStd.h StepStrategyStd.cpp
        EatStrategyStd.h EatStrategyStd.cpp
        KillStrategyStd.h KillStrategyStd.cpp
        FindPlaceStrategyStd.h FindPlaceStrategyStd.cpp
        BornStrategyStd.h BornStrategyStd.cpp
        Player.h Player.cpp
        PlayersList.cpp PlayersList.h
)

find_package(Protobuf REQUIRED)
target_link_libraries(engine PUBLIC ${PROTOBUF_LIBRARIES} proto)