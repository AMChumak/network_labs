//
// Created by anton on 12/9/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../snakes.pb.h"

namespace gameEngine {

class Player {
public:
    virtual ~Player() = default;
    Player (int iId, std::string iname, int score = 0);
    int getPlayerId();
    std::string getName();
    virtual void showState(GameState state)=0;
    virtual void showCommandResult(GameMessage message)=0;
    virtual GamePlayer getDescription()=0;
public:
    int score_;
private:
    int id_;
    std::string name;
};

} // gameEngine

#endif //PLAYER_H
