//
// Created by anton on 12/9/24.
//

#ifndef PLAYER_H
#define PLAYER_H

namespace gameEngine {

class Player {
public:
    Player (int iId);
    int getPlayerId();
    int score_;
private:
    int id_;
};

} // gameEngine

#endif //PLAYER_H
