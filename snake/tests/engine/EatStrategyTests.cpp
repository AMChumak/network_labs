#include "../../src/engine/FoodDistributor.h"
#include "../../src/engine/EatStrategyStd.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class EatStrategyTests : public ::testing::Test
{
protected:
    int first_user_id = 1;
    int second_user_id = 2;
    Coord first_start_position{3, 3};
    Direction first_start_direction = Direction::RIGHT;
    Coord second_start_position{4, 5};
    Direction second_start_direction = Direction::UP;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Snake>> snakes;
    std::shared_ptr<FoodDistributor> food_distributor;
protected:
    EatStrategyTests()
    {
        field = std::make_shared<Field>(10, 6);
        snakes = std::make_shared<std::vector<Snake>>();
        food_distributor = std::make_shared<FoodDistributor>(field, snakes);
        snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
        snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    }
};


TEST_F(EatStrategyTests, std_eat_test)
{
    GameState state;
    auto state_food = state.add_foods();
    state_food->set_x(first_start_position.x);
    state_food->set_y(first_start_position.y);
    state_food = state.add_foods();
    state_food->set_x(second_start_position.x);
    state_food->set_y(second_start_position.y);
    food_distributor->fill_food(state);
    food_distributor->refill_food();
    Coord rest_food = food_distributor->get_foods().at(2);

    EatStrategyStd eat_strategy;
    eat_strategy.eat(snakes, food_distributor);

    auto rest = food_distributor->get_foods();

    ASSERT_EQ(rest.size(), 1);
    ASSERT_EQ(rest[0], rest_food);

    auto first_body = snakes->at(0).get_body();
    auto second_body = snakes->at(1).get_body();

    ASSERT_EQ(first_body.size(), 3);
    Coord first_body_center = field->canonize_coord(first_start_position + Coord{-1, 0});
    Coord first_body_tail = field->canonize_coord(first_start_position + Coord{-2, 0});
    ASSERT_EQ(first_body[0], first_start_position);
    ASSERT_EQ(first_body[1], first_body_center);
    ASSERT_EQ(first_body[2], first_body_tail);

    ASSERT_EQ(second_body.size(), 3);
    Coord second_body_center = field->canonize_coord(second_start_position + Coord{0, 1});
    Coord second_body_tail = field->canonize_coord(second_start_position + Coord{0, 2});
    ASSERT_EQ(second_body[0], second_start_position);
    ASSERT_EQ(second_body[1], second_body_center);
    ASSERT_EQ(second_body[2], second_body_tail);
}