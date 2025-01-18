#include "../../src/engine/Snake.h"
#include "../../src/engine/KillStrategyStd.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class KillStrategyTests : public ::testing::Test
{
protected:
    int first_user_id = 1;
    int second_user_id = 2;
    Coord first_start_position{3, 3};
    Direction first_start_direction = Direction::RIGHT;
    Coord second_start_position{3, 3};
    Direction second_start_direction = Direction::UP;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Snake>> snakes;

protected:
    KillStrategyTests()
    {
        field = std::make_shared<Field>(10, 6);
        snakes = std::make_shared<std::vector<Snake>>();
        snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
        snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    }
};

TEST_F(KillStrategyTests, kill_one_snake_test)
{
    snakes->at(0).step();
    KillStrategyStd kill_strategy;
    kill_strategy.kill(snakes);

    ASSERT_EQ(snakes->size(), 1);
    ASSERT_EQ(snakes->at(0).get_owner_id(), first_user_id);
}

TEST_F(KillStrategyTests, kill_all_snake_test)
{
    KillStrategyStd kill_strategy;
    kill_strategy.kill(snakes);

    ASSERT_EQ(snakes->size(), 0);
}