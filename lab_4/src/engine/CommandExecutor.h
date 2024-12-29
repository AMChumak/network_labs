//
// Created by anton on 12/9/24.
//

#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include "Commands.h"
#include "FoodDistributor.h"
#include "Player.h"
#include "PlayersList.h"

namespace gameEngine
{
    struct CommandI;
    struct CommandCreate;
    struct CommandTurn;


    class CommandExecutor
    {
        enum ExecutorState
        {
            ACTION = 0,
            CREATION
        };

    public:
        CommandExecutor(std::shared_ptr<Field> iFieldp, std::shared_ptr<std::vector<Snake>> iSnakes,
                        std::shared_ptr<FoodDistributor> iFoodDistr, std::shared_ptr<PlayersList> iPlayersList);
        void executeActionCommands(std::shared_ptr<std::vector<CommandI>> commands);
        void executeCreationCommands(std::shared_ptr<std::vector<CommandI>> commands);
        void execute(const CommandCreate& command);
        void execute(const CommandTurn& command);

    private:
        ExecutorState state = ACTION;
        std::shared_ptr<Field> fieldp;
        std::shared_ptr<std::vector<Snake>> snakes;
        std::shared_ptr<FoodDistributor> foodDistributor;
        std::shared_ptr<PlayersList> players;
    };
} // gameEngine

#endif //COMMANDEXECUTOR_H
