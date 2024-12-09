//
// Created by anton on 12/9/24.
//

#include "Player.h"

namespace gameEngine {
    Player::Player(int iId): id_{iId}
    {
    }

    int Player::getPlayerId()
    {
        return id_;
    }
} // gameEngine