//
// Created by anton on 1/18/25.
//

#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H
#include "Player.h"
#include "PlayersListObserver.h"
#include "proto/snakes.pb.h"

namespace engine
{
    class PlayersList
    {
    public:
        static Player invalid_player;
        PlayersList();
        PlayersList(const GamePlayers& players);

        int get_available_id();

        const std::vector<Player>& get_players() const;
        Player& get_player(int player_id);

        int add_player(std::string i_name, int i_score);
        int add_player(int player_id, std::string i_name, int i_score);

        void erase_player(int player_id);
        std::vector<Player>::const_iterator erase_player(std::vector<Player>::const_iterator iter);

        void add_observer(std::shared_ptr<PlayersListObserver> observer);
        void remove_observer(std::shared_ptr<PlayersListObserver> observer);
    private:
        std::mutex set_mutex;
        std::mutex observers_mutex;
        std::set<int> ids_set;
        std::vector<Player> players;
        std::vector<std::shared_ptr<PlayersListObserver>> observers;
    };
} // engine

#endif //PLAYERSLIST_H
