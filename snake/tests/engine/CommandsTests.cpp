#include "../../src/engine/Snake.h"
#include "../../src/engine/CommandExecutor.h"
#include "../../src/engine/CommandsQueue.h"
#include <memory>
#include <gtest/gtest.h>

using namespace engine;

class CommandsTests : public ::testing::Test
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
    CommandsQueue queue;
    std::shared_ptr<PlayersList> list;
    std::shared_ptr<FoodDistributor> food_distributor;
protected:
    CommandsTests()
    {
        field = std::make_shared<Field>(10, 6);
        snakes = std::make_shared<std::vector<Snake>>();
        food_distributor = std::make_shared<FoodDistributor>(field, snakes);
        list = std::make_shared<PlayersList>();
        //snakes->emplace_back(first_user_id, first_start_position, first_start_direction, field);
        //snakes->emplace_back(second_user_id, second_start_position, second_start_direction, field);
    }
};


TEST_F(CommandsTests, commands_queue_test)
{
    int first_id = list->add_player("first",0);

    std::shared_ptr<CommandCreate> command = std::make_shared<CommandCreate>();
    command->user_id = first_id;

    queue.add_command(command);

    auto &extracted_commands = queue.extract_commands();
    ASSERT_EQ(1, extracted_commands.size());
    ASSERT_EQ(first_id, extracted_commands.at(0)->user_id);

    auto &second_try = queue.get_extracted_commands();
    ASSERT_EQ(1, second_try.size());
    ASSERT_EQ(first_id, second_try.at(0)->user_id);
}


TEST_F(CommandsTests, executor_command_create_test)
{
    const int first_id = list->add_player("first",0);
    const int second_id = list->add_player("second",0);

    const auto first_create_command = std::make_shared<CommandCreate>();
    const auto second_create_command = std::make_shared<CommandCreate>();
    first_create_command->user_id = first_id;
    second_create_command->user_id = second_id;
    const auto first_turn_command = std::make_shared<CommandTurn>();
    first_turn_command->user_id = first_id;
    first_turn_command->direction = UP;


    queue.add_command(first_create_command);
    queue.add_command(first_turn_command);
    queue.add_command(second_create_command);

    std::vector<std::shared_ptr<CommandI>> &extracted_commands = queue.extract_commands();

    ASSERT_EQ(3, extracted_commands.size());

    CommandExecutor executor{field,snakes, food_distributor,list};

    executor.execute_creation_commands(extracted_commands);
    ASSERT_EQ(snakes->size(), 2);
}

TEST_F(CommandsTests, executor_command_turn_test)
{
    const int first_id = list->add_player("first",0);
    snakes->clear();
    snakes->emplace_back(first_id, first_start_position, first_start_direction, field);

    const auto first_turn_command = std::make_shared<CommandTurn>();
    first_turn_command->user_id = first_id;
    first_turn_command->direction = UP;

    queue.add_command(first_turn_command);


    std::vector<std::shared_ptr<CommandI>> &extracted_commands = queue.extract_commands();

    ASSERT_EQ(1, extracted_commands.size());

    CommandExecutor executor{field,snakes, food_distributor,list};

    executor.execute_action_commands(extracted_commands);
    ASSERT_EQ(snakes->at(0).get_head_direction(), UP);
}