#include "../../src/engine/Snake.h"
#include "../../src/engine/StepStrategyStd.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class StepStrategyTests : public ::testing::Test
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

protected:
    StepStrategyTests()
    {
        field = std::make_shared<Field>(10, 6);
        snakes = std::make_shared<std::vector<Snake>>();
        snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
        snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    }
};


TEST_F(StepStrategyTests, step_test)
{
    StepStrategyStd step_strategy;

    step_strategy.step(snakes);

    auto first_body = snakes->at(0).get_body();
    auto second_body = snakes->at(1).get_body();

    Coord first_body_head = first_start_position + Coord{1, 0};
    ASSERT_EQ(first_body[0], first_body_head);
    ASSERT_EQ(first_body[1], first_start_position);

    Coord second_body_head = second_start_position + Coord{0, -1};
    ASSERT_EQ(second_body[0], second_body_head);
    ASSERT_EQ(second_body[1], second_start_position);
}