//
// Created by anton on 1/18/25.
//

#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H
#include "Player.h"
#include "proto/snakes.pb.h"

namespace engine
{
    class PlayersList
    {
    public:
        static Player invalid_player;
        PlayersList();
        PlayersList(const GamePlayers& players);

        const std::vector<Player>& get_players() const;
        Player& get_player(int player_id);

        int add_player(std::string i_name, int i_score);

        void erase_player(int player_id);
        std::vector<Player>::const_iterator erase_player(std::vector<Player>::const_iterator iter);

    private:
        int get_first_available_id() const;

    private:
        std::set<int> ids_set;
        std::vector<Player> players;
    };
} // engine

#endif //PLAYERSLIST_H
