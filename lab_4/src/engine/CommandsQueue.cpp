//
// Created by anton on 12/9/24.
//

#include "CommandsQueue.h"

#include <memory>

namespace gameEngine {
    void CommandsQueue::addCommand(const CommandI& command)
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        commandsQ.push_back(command);
    }

    std::shared_ptr<std::vector<CommandI>> CommandsQueue::extractCommands()
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        auto extracted = std::make_shared<std::vector<CommandI>>(commandsQ);
        commandsQ.clear();
        extractedCommandsQ = extracted;
        return extractedCommandsQ;
    }

    std::shared_ptr<std::vector<CommandI>> CommandsQueue::getExtractedCommands()
    {
        return extractedCommandsQ;
    }

    void CommandsQueue::deleteExtractedCommands()
    {
        extractedCommandsQ = nullptr;
    }
} // gameEngine