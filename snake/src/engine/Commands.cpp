//
// Created by anton on 12/9/24.
//

#include "Commands.h"

using namespace engine;

void CommandI::visit(CommandExecutor &executor)
{
}

CommandCreate::CommandCreate(int user_id)
{
    this->user_id = user_id;
};

void CommandCreate::visit(CommandExecutor &executor)
{
    executor.execute(*this);
}

CommandTurn::CommandTurn(int user_id, Direction direction)
{
    this->user_id = user_id;
    this->direction = direction;
}


void CommandTurn::visit(CommandExecutor &executor)
{
    executor.execute(*this);
}

