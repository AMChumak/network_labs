//
// Created by anton on 12/9/24.
//

#include "Commands.h"

using namespace engine;

void CommandI::visit(CommandExecutor &executor)
{
}

void CommandCreate::visit(CommandExecutor &executor)
{
    executor.execute(*this);
}


void CommandTurn::visit(CommandExecutor &executor)
{
    executor.execute(*this);
}

