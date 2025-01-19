//
// Created by anton on 12/9/24.
//

#ifndef COMMANDI_H
#define COMMANDI_H
#include "CommandExecutor.h"
#include "proto/snakes.pb.h"

namespace engine
{
    class CommandExecutor;
    class CommandsQueue;

    struct CommandI
    {
        virtual ~CommandI() = default;
        virtual void visit(CommandExecutor &executor) =0;
        int user_id;
    };

    struct CommandCreate : public CommandI
    {
        CommandCreate() = default;
        CommandCreate(int user_id);
        void visit(CommandExecutor &executor) override;
    };

    struct CommandTurn : public CommandI
    {
        CommandTurn() = default;
        CommandTurn(int user_id, Direction direction);
        void visit(CommandExecutor &executor) override;
        Direction direction;
    };
} // engine

#endif //COMMANDI_H
