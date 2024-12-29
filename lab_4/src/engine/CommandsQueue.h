//
// Created by anton on 12/9/24.
//

#ifndef COMMANDSQUEUE_H
#define COMMANDSQUEUE_H
#include <mutex>
#include <vector>

#include "Commands.h"

namespace gameEngine {

class CommandsQueue {
public:
    void addCommand(const CommandI &command);
    std::shared_ptr<std::vector<CommandI>> extractCommands();
    std::shared_ptr<std::vector<CommandI>> getExtractedCommands();
    void deleteExtractedCommands();

private:
    std::mutex queueMtx;
    std::vector<CommandI> commandsQ;
    std::shared_ptr<std::vector<CommandI>> extractedCommandsQ = nullptr;
};

} // gameEngine

#endif //COMMANDSQUEUE_H
