//
// Created by anton on 1/19/25.
//

#include "CommandExecutor.h"

#include "BornStrategyStd.h"
#include "Commands.h"
#include "FindPlaceStrategyStd.h"

namespace engine
{
    CommandExecutor::CommandExecutor(const std::shared_ptr<Field>& i_field, const std::shared_ptr<std::vector<Snake>>& i_snakes,
                                     const std::shared_ptr<FoodDistributor>& i_food_distributor,
                                     const std::shared_ptr<PlayersList>& i_players_list) : field(i_field), snakes(i_snakes),
        food_distributor(i_food_distributor), players_list(i_players_list)
    {
    }

    void CommandExecutor::execute_action_commands(std::vector<std::shared_ptr<CommandI>> &commands)
    {
        state = ACTION;
        for (auto &command : commands)
        {
            command->visit(*this);
        }
    }

    void CommandExecutor::execute_creation_commands(std::vector<std::shared_ptr<CommandI>> &commands)
    {
        state = CREATION;
        for (auto &command : commands)
        {
            command->visit(*this);
        }
    }

    void CommandExecutor::execute(const CommandCreate& command) const
    {
        if (state != CREATION)
            return;

        BornStrategyStd strategy;
        auto find_place_strategy = std::make_shared<FindPlaceStrategyStd>();
        bool res = strategy.born(command.user_id, snakes, food_distributor, field, find_place_strategy);
        if (!res)
        {
            players_list->erase_player(command.user_id);
        }
    }

    void CommandExecutor::execute(const CommandTurn& command) const
    {
        if (state != ACTION)
            return;
        for (auto &snake : *snakes)
        {
            if (snake.get_owner_id() == command.user_id)
            {
                snake.turn(command.direction); //I don't break for multi-snake management for one user
            }
        }
    }
} // engine
