//
// Created by anton on 1/19/25.
//

#include "CommandsQueue.h"

using namespace engine;

void CommandsQueue::add_command(const std::shared_ptr<CommandI>& command)
{
    std::lock_guard<std::mutex> lock{q_mutex};
    commands.push_back(command);
}

std::vector<std::shared_ptr<CommandI>>& CommandsQueue::extract_commands()
{
    std::lock_guard<std::mutex> lock{q_mutex};
    extracted_commands = commands;
    commands.clear();
    return extracted_commands;
}

std::vector<std::shared_ptr<CommandI>>& CommandsQueue::get_extracted_commands()
{
    std::lock_guard<std::mutex> lock{q_mutex};
    return extracted_commands;
}
