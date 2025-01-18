//
// Created by anton on 12/9/24.
//

#include "Player.h"

namespace gameEngine {
    Player::Player(int iId, std::string iName, int score): id_{iId}, name{iName}, score_{score}
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