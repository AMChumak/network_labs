#include "../../src/engine/FoodDistributor.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class FoodDistributorTests : public ::testing::Test
{
protected:
    int first_user_id = 1;
    int second_user_id = 2;
    Coord start_position{3, 3};
    Direction start_direction = Direction::RIGHT;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Snake>> snakes;
    std::shared_ptr<FoodDistributor> food_distributor;
protected:
    FoodDistributorTests()
    {
        field = std::make_shared<Field>(10, 6);
        snakes = std::make_shared<std::vector<Snake>>();
        food_distributor = std::make_shared<FoodDistributor>(field, snakes);
    }
};

TEST_F(FoodDistributorTests, food_distributor_refill_test)
{
    food_distributor->refill_food();
    const std::vector<Coord> &foods = food_distributor->get_foods();
    ASSERT_EQ(foods.size(), 1);
}

TEST_F(FoodDistributorTests, food_refill_with_snake_test)
{
    snakes->emplace_back(first_user_id,start_position, start_direction, field);
    food_distributor->refill_food();
    const std::vector<Coord> &foods = food_distributor->get_foods();
    ASSERT_EQ(foods.size(), 2);
    ASSERT_NE(foods[0], foods[1]);
    for (auto cell : snakes->at(0).get_body())
    {
        for (auto food : foods)
        {
            ASSERT_NE(food, cell);
        }
    }
}

TEST_F(FoodDistributorTests, food_fill_by_state_test)
{
    GameState state;
    auto state_food = state.add_foods();
    state_food->set_x(3);
    state_food->set_y(3);
    food_distributor->fill_food(state);
    const std::vector<Coord> &foods = food_distributor->get_foods();
    ASSERT_EQ(foods.size(), 1);
    Coord check{3, 3};
    ASSERT_EQ(foods[0], check);
}


TEST_F(FoodDistributorTests, food_erase_test)
{
    snakes->emplace_back(first_user_id,start_position, start_direction, field);
    food_distributor->refill_food();
    const std::vector<Coord> &foods = food_distributor->get_foods();
    ASSERT_EQ(foods.size(), 2);
    ASSERT_NE(foods[0], foods[1]);
    Coord check = foods[1];
    food_distributor->erase_food(foods.begin());
    ASSERT_EQ(check, foods.front());
}