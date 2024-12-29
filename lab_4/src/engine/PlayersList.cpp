//
// Created by anton on 12/12/24.
//

#include "PlayersList.h"

#include <memory>

#include "OnlinePlayer.h"

namespace gameEngine {
    PlayersList::PlayersList(const google::protobuf::RepeatedPtrField<GamePlayer>& gamePlayers)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        maxId = 1;
        for (auto player : gamePlayers)
        {
            //auto playerPtr = std::make_shared<OnlinePlayer>(player.id(), player.name(), player.score()) todo надо как-то добавить netMember
        }
    }

    void PlayersList::addPlayer(std::shared_ptr<Player> player)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        players.push_back(player);
    }

    void PlayersList::removePlayer(const int& id)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        for(int i = 0; i < players.size(); ++i)
        {
            if (players[i]->getPlayerId() == id)
            {
                players.erase(players.begin() + id);
                return;
            }
        }
    }

    std::shared_ptr<Player> PlayersList::getPlayer(const int& id)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        for(auto & player : players)
        {
            if (player->getPlayerId() == id)
            {
                return std::make_shared<Player>(player->getPlayerId(),player->getName(), player->score_);
            }
        }
        return std::make_shared<Player>(-1, std::string());
    }
} // gameEngine