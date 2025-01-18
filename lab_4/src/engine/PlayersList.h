//
// Created by anton on 12/12/24.
//

#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H
#include <mutex>

#include "Player.h"

namespace gameEngine {

class PlayersList {
public:
    PlayersList();
    PlayersList(const ::google::protobuf::RepeatedPtrField< ::GamePlayer >& gamePlayers);
    int addPlayer(const std::string& name, const int &score = 0);
    void removePlayer(const int &id);
    Player &getPlayer(const int &id);

    static Player incorrectPlayer;
private:
    std::mutex stateMtx;
    std::vector<Player> players;
    int maxId = 0;
};
} // gameEngine

#endif //PLAYERSLIST_H
