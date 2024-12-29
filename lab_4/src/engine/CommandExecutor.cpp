//
// Created by anton on 12/9/24.
//

#include "CommandExecutor.h"

#include <memory>

#include "BornStrategyStd.h"
#include "FindPlaceStrategyStd.h"
#include "Commands.h"

namespace gameEngine
{
    CommandExecutor::CommandExecutor(std::shared_ptr<Field> iFieldp, std::shared_ptr<std::vector<Snake>> iSnakes,
                                     std::shared_ptr<FoodDistributor> iFoodDistr, std::shared_ptr<PlayersList> iPlayersList)
        : fieldp{iFieldp}, snakes{iSnakes}, foodDistributor{iFoodDistr}, players{iPlayersList}
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
            bool res = strategy.born(command.userId, snakes, foodDistributor, fieldp, findPlaceStrategy);


            std::shared_ptr<Player> owner = players->getPlayer(command.userId);
            if(owner->getPlayerId() == -1)
            {
                std::cerr << "user was deleted before creating ended" << std::endl;
                return;
            }
            if (res)
            {
                GameMessage msg;
                GameMessage_AckMsg ack_msg;
                msg.set_allocated_ack(&ack_msg);
                owner->showCommandResult(msg);
            } else
            {
                GameMessage msg;
                GameMessage_ErrorMsg err_msg;
                err_msg.set_error_message("place was not found :(");
                msg.set_allocated_error(&err_msg);
                owner->showCommandResult(msg);
            }
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
