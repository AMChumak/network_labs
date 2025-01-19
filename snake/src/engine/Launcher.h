//
// Created by anton on 1/19/25.
//

#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "CommandExecutor.h"
#include "CommandsQueue.h"
#include "ConfigKeeper.h"
#include "Player.h"
#include "proto/snakes.pb.h"

namespace engine
{
    class Launcher
    {
    public:
        void launch();
        void launch(const GameState& state, const GameConfig& config);

        int add_player(const std::string &name, const int &score) const;
        void add_creation_command(int player_id) const;
        void add_turn_command(int player_id, Direction direction) const;

        void add_observer(const std::shared_ptr<PlayersListObserver>& observer) const;
        void remove_observer(const std::shared_ptr<PlayersListObserver>& observer) const;


    private:
        void create_game_state();
        void main_loop();

    private:
        std::mutex state_mutex;
        GameState state;

        int state_order = 0;
        ConfigKeeper config_keeper;
        std::shared_ptr<CommandExecutor> command_executor;
        std::shared_ptr<CommandsQueue> commands_queue;
        std::shared_ptr<PlayersList> players_list;
        std::shared_ptr<std::vector<Snake>> game_snakes;
        std::shared_ptr<FoodDistributor> game_food_distributor;
        std::shared_ptr<Field> game_field;
    };
} // engine

#endif //LAUNCHER_H
