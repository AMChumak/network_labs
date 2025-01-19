#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <vector>
#include "Commands.h"

namespace engine
{
    class CommandsQueue
    {
    public:
        void add_command(const std::shared_ptr<CommandI>& command);
        std::vector<std::shared_ptr<CommandI>>& extract_commands();
        std::vector<std::shared_ptr<CommandI>>& get_extracted_commands();

    private:
        std::mutex q_mutex;
        std::vector<std::shared_ptr<CommandI>> commands;
        std::vector<std::shared_ptr<CommandI>> extracted_commands;
    };
} // engine

#endif //COMMANDQUEUE_H
