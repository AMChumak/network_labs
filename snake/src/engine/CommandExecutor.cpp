//
// Created by anton on 1/19/25.
//

#include "CommandExecutor.h"

#include "BornStrategyStd.h"
#include "Commands.h"
#include "FindPlaceStrategyStd.h"

namespace engine
{
    CommandExecutor::CommandExecutor(std::shared_ptr<Field> i_field, std::shared_ptr<std::vector<Snake>> i_snakes,
                                     std::shared_ptr<FoodDistributor> i_food_distributor,
                                     std::shared_ptr<PlayersList> i_players_list) : field(i_field), snakes(i_snakes),
        food_distributor(i_food_distributor), players_list(i_players_list)
    {
    }

    void CommandExecutor::execute_action_commands(std::vector<CommandI> &commands)
    {
        state = ACTION;
        for (auto &command : commands)
        {
            command.visit(*this);
        }
    }

    void CommandExecutor::execute_creation_commands(std::vector<CommandI> &commands)
    {
        state = CREATION;
        for (auto &command : commands)
        {
            command.visit(*this);
        }
    }

    void CommandExecutor::execute(const CommandCreate& command)
    {
        if (state != CREATION)
            return;

        BornStrategyStd strategy;
        auto find_place_strategy = std::make_shared<FindPlaceStrategyStd>();
        bool res = strategy.born(command.user_id, snakes, food_distributor, field, find_place_strategy);
        
    }

    void CommandExecutor::execute(const CommandTurn& command)
    {

    }
} // engine
