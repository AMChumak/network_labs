//
// Created by anton on 12/9/24.
//

#ifndef COMMANDI_H
#define COMMANDI_H
#include "CommandExecutor.h"
#include "Snake.h"
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
        void visit(CommandExecutor &executor) override;
    };

    struct CommandTurn : public CommandI
    {
        void visit(CommandExecutor &executor) override;
        ::Direction direction;
    };
} // engine

#endif //COMMANDI_H
