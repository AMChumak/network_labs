//
// Created by anton on 12/9/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../snakes.pb.h"

namespace gameEngine {

class Player {
public:
    Player (int iId, std::string iName, int score = 0);
    int getPlayerId();
    std::string getName();
public:
    int score_;
private:
    int id_;
    std::string name;
};

} // gameEngine

#endif //PLAYER_H
