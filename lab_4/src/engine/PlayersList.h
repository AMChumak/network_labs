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
    PlayersList(const ::google::protobuf::RepeatedPtrField< ::GamePlayer >& gamePlayers);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(const int &id);
    std::shared_ptr<Player> getPlayer(const int &id);
};
    std::mutex stateMtx;
    std::vector<std::shared_ptr<Player>> players;
    int maxId = 1;

} // gameEngine

#endif //PLAYERSLIST_H
