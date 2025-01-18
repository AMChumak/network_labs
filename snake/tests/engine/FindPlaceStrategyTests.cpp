#include "../../src/engine/FoodDistributor.h"
#include "../../src/engine/FindPlaceStrategyStd.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class FindPlaceStrategyTests : public ::testing::Test
{
protected:
    int first_user_id = 1;
    int second_user_id = 2;
    int third_user_id = 3;
    int fourth_user_id = 4;
    Coord first_start_position{0, 0};
    Direction first_start_direction = UP;
    Coord second_start_position{2, 0};
    Direction second_start_direction = UP;
    Coord third_start_position{0, 4};
    Direction third_start_direction = UP;
    Coord fourth_start_position{4, 4};
    Direction fourth_start_direction = RIGHT;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Snake>> snakes;
    std::shared_ptr<FoodDistributor> food_distributor;
protected:
    FindPlaceStrategyTests()
    {
        field = std::make_shared<Field>(6, 7);
        snakes = std::make_shared<std::vector<Snake>>();
        food_distributor = std::make_shared<FoodDistributor>(field, snakes);
    }
};


TEST_F(FindPlaceStrategyTests, successful_search_test)
{
    FindPlaceStrategyStd find_place_strategy;
    CoordDirectionPair pair = find_place_strategy.find_place(snakes, food_distributor, field);

    ASSERT_NE(pair.coord, incorrect_pair.coord);
}

TEST_F(FindPlaceStrategyTests, failed_by_snakes_search_test)
{
    snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
    snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    snakes->emplace_back(fourth_user_id, fourth_start_position, fourth_start_direction, field);
    FindPlaceStrategyStd find_place_strategy;
    const CoordDirectionPair pair = find_place_strategy.find_place(snakes, food_distributor, field);

    ASSERT_EQ(pair.coord, incorrect_pair.coord);
}

TEST_F(FindPlaceStrategyTests, failed_by_food_search_test)
{
    snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
    snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    snakes->emplace_back(third_user_id, third_start_position, third_start_direction, field);

    GameState state;
    auto state_food = state.add_foods();
    state_food->set_x(3);
    state_food->set_y(3);
    state_food = state.add_foods();
    state_food->set_x(3);
    state_food->set_y(5);
    state_food = state.add_foods();
    state_food->set_x(2);
    state_food->set_y(4);
    state_food = state.add_foods();
    state_food->set_x(4);
    state_food->set_y(4);
    food_distributor->fill_food(state);

    FindPlaceStrategyStd find_place_strategy;
    const CoordDirectionPair pair = find_place_strategy.find_place(snakes, food_distributor, field);

    ASSERT_EQ(pair.coord, incorrect_pair.coord);
}

TEST_F(FindPlaceStrategyTests, success_only_one_available_pair_test)
{
    snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
    snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    snakes->emplace_back(third_user_id, third_start_position, third_start_direction, field);

    GameState state;
    auto state_food = state.add_foods();
    state_food->set_x(3);
    state_food->set_y(3);
    state_food = state.add_foods();
    state_food->set_x(3);
    state_food->set_y(5);
    state_food = state.add_foods();
    state_food->set_x(2);
    state_food->set_y(4);
    state_food = state.add_foods();
    state_food->set_x(5);
    state_food->set_y(5);
    food_distributor->fill_food(state);

    FindPlaceStrategyStd find_place_strategy;
    const CoordDirectionPair pair = find_place_strategy.find_place(snakes, food_distributor, field);

    Coord check_center{3,4};
    ASSERT_EQ(pair.coord, check_center);
    ASSERT_EQ(pair.direction, LEFT);
}