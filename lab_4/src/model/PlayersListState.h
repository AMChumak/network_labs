//
// Created by anton on 12/12/24.
//

#ifndef PLAYERSLISTSTATE_H
#define PLAYERSLISTSTATE_H
#include <mutex>
#include <string>

#include "net/ConnectionsList.h"

using namespace netEngine;

namespace modelSpace {

struct PlayerState
{
    std::string name;
    int id;
    std::string address;
    int port;
    NodeRole role;
    int score;
};

class PlayersListState {
public:
    std::vector<PlayerState> getPlayers();
    int getMyId() const;
    void setMyId(int newId);
    void generateList(const GamePlayers& gamePlayers, const std::string& senderAddr = "", int senderPort = -1);
private:
    int myId = 0;
    std::vector<PlayerState> players;
    std::mutex stateMtx;
    bool isUpdated = false;
};

} // modelSpace

#endif //PLAYERSLISTSTATE_H
