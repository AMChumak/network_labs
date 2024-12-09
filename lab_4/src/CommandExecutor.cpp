//
// Created by anton on 12/9/24.
//

#include "CommandExecutor.h"

#include <memory>

#include "BornStrategyStd.h"
#include "FindPlaceStrategyStd.h"
#include "Commands.h"
namespace gameEngine {
    CommandExecutor::CommandExecutor(std::shared_ptr<Field> iFieldp, std::shared_ptr<std::vector<Snake>> iSnakes) : fieldp{iFieldp}, snakes{iSnakes}
    {
    }

    void CommandExecutor::executeActionCommands(std::shared_ptr<std::vector<CommandI>> commands)
    {
        state = ACTION;
        for (auto command : *commands)
        {
            command.visit(this);
        }
    }

    void CommandExecutor::executeCreationCommands(std::shared_ptr<std::vector<CommandI>> commands)
    {
        state = CREATION;
        for (auto command : *commands)
        {
            command.visit(this);
        }
    }

    void CommandExecutor::execute(const CommandCreate& command)
    {
        if (state == CREATION)
        {
            BornStrategyStd strategy;
            auto findPlaceStrategy = std::make_shared<FindPlaceStrategyStd>();
            strategy.born(command.userId, snakes, foodDistributor, fieldp, findPlaceStrategy);
        }
    }

    void CommandExecutor::execute(const CommandTurn& command)
    {
        if (state == ACTION)
        {
            for (auto snake : *snakes)
            {
                if (snake.getOwnerId() == command.userId)
                {
                    snake.turn(command.direction);
                }
            }
        }
    }
} // gameEngine