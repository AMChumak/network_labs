//
// Created by anton on 1/19/25.
//

#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <memory>
#include <vector>

#include "Field.h"
#include "FoodDistributor.h"
#include "PlayersList.h"
#include "Snake.h"

namespace engine
{
    struct CommandI;
    struct CommandCreate;
    struct CommandTurn;

    class CommandExecutor
    {
    private:
        enum ExecutorState
        {
            ACTION = 0,
            CREATION
        };

    public:
        CommandExecutor(const std::shared_ptr<Field>& i_field, const std::shared_ptr<std::vector<Snake>>& i_snakes,
                        const std::shared_ptr<FoodDistributor>& i_food_distributor, const std::shared_ptr<PlayersList>& i_players_list);
        void execute_action_commands(std::vector<std::shared_ptr<CommandI>> &commands);
        void execute_creation_commands(std::vector<std::shared_ptr<CommandI>> &commands);
        void execute(const CommandCreate& command) const;
        void execute(const CommandTurn& command) const;

    private:
        ExecutorState state = ACTION;
        std::shared_ptr<Field> field;
        std::shared_ptr<std::vector<Snake>> snakes;
        std::shared_ptr<FoodDistributor> food_distributor;
        std::shared_ptr<PlayersList> players_list;
    };
} // engine

#endif //COMMANDEXECUTOR_H
