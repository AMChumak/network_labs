//
// Created by anton on 12/12/24.
//

#include "PlayersListState.h"

namespace modelSpace
{
    std::vector<PlayerState> PlayersListState::getPlayers()
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        isUpdated = false;
        return players;
    }

    int PlayersListState::getMyId() const
    {
        return myId;
    }

    void PlayersListState::setMyId(const int newId)
    {
        myId = newId;
    }

    void PlayersListState::generateList(const GamePlayers& gamePlayers, const std::string& senderAddr, int senderPort)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        players.clear();
        for (const GamePlayer& player : gamePlayers.players())
        {
            std::string curPlayerAddr = senderAddr;
            int curPlayerPort = senderPort;

            if (player.has_ip_address())
            {
                curPlayerAddr = player.ip_address();
            }

            if (player.has_port())
            {
                curPlayerPort = player.port();
            }

            players.emplace_back(player.name(), player.id(), curPlayerAddr, curPlayerPort, player.role(),
                                 player.score());
        }

        isUpdated = true;
    }
} // modelSpace
