//
// Created by anton on 12/9/24.
//

#ifndef COMMANDI_H
#define COMMANDI_H
#include "CommandExecutor.h"
#include "Snake.h"

namespace gameEngine
{
    class CommandExecutor;

    struct CommandI
    {
        int userId;
        virtual void visit(CommandExecutor* executor);
    };

    struct CommandCreate : public CommandI
    {
        void visit(CommandExecutor* executor) override;
    };

    struct CommandTurn : public CommandI
    {
        void visit(CommandExecutor* executor) override;
        Direction direction;
    };
} // gameEngine

#endif //COMMANDI_H
