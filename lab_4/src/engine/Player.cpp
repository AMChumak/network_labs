//
// Created by anton on 12/9/24.
//

#include "Player.h"

namespace gameEngine {
    Player::Player(int iId, std::string iname, int score): id_{iId}, name{iname}, score_{score}
    {
    }

    int Player::getPlayerId()
    {
        return id_;
    }

    std::string Player::getName()
    {
        return name;
    }

} // gameEngine