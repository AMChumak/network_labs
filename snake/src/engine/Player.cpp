//
// Created by anton on 12/9/24.
//

#include "Player.h"

namespace engine {
    Player::Player(const int i_id, const std::string& i_name, const int i_score): score{i_score}, id{i_id}, name{i_name}
    {
    }

    /*!
     *
     * @return state of player (only id, name, score)
     */
    GamePlayer Player::generate_state() const
    {
        GamePlayer player_state;
        player_state.set_id(id);
        player_state.set_name(name);
        player_state.set_score(score);
        return player_state;
    }

    int Player::get_player_id() const
    {
        return id;
    }

    std::string Player::get_name()
    {
        return name;
    }

} // engine