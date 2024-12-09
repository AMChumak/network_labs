//
// Created by anton on 12/9/24.
//

#include "Commands.h"


void gameEngine::CommandI::visit(CommandExecutor* executor)
{
}

void gameEngine::CommandCreate::visit(CommandExecutor* executor)
{
    executor->execute(*this);
}

void gameEngine::CommandTurn::visit(CommandExecutor* executor)
{
    executor->execute(*this);
}

