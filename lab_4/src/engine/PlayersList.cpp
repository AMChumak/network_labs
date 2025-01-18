//
// Created by anton on 12/12/24.
//

#include "PlayersList.h"

#include <memory>

gameEngine::Player gameEngine::PlayersList::incorrectPlayer = Player{-1, std::string(), 0};

namespace gameEngine {
    PlayersList::PlayersList()
    {
    }

    PlayersList::PlayersList(const google::protobuf::RepeatedPtrField<GamePlayer>& gamePlayers)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        maxId = 0;
        for (const auto &player : gamePlayers)
        {
            players.emplace_back(player.id(), player.name(), player.score());
            if (player.id() > maxId)
            {
                maxId = player.id();
            }
        }
    }

    int PlayersList::addPlayer(const std::string& name, const int &score)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        players.emplace_back(++maxId, name, score);
        return maxId;
    }

    void PlayersList::removePlayer(const int& id)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        for(int i = 0; i < players.size(); ++i)
        {
            if (players[i].getPlayerId() == id)
            {
                players.erase(players.begin() + id);
                return;
            }
        }
    }

    Player &PlayersList::getPlayer(const int& id)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        for(auto & player : players)
        {
            if (player.getPlayerId() == id)
            {
                return player;
            }
        }
        return incorrectPlayer;
    }
} // gameEngine