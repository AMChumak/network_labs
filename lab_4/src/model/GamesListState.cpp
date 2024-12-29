//
// Created by anton on 12/12/24.
//

#include "GamesListState.h"

namespace modelSpace {
    void GamesListState::addNewGame(const GameAnnouncement& announcement)
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        games.push_back(announcement);
    }

    void GamesListState::clearList()
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        games.clear();
    }

    std::vector<GameAnnouncement> GamesListState::getGames()
    {
        std::lock_guard<std::mutex> lock(stateMtx);
        return games;
    }

    GameAnnouncement GamesListState::getGameByName(const std::string& gameName)
    {
        std::lock_guard<std::mutex> lock(stateMtx);

        for(auto announcement :games)
        {
            if (announcement.game_name() == gameName)
            {
                return announcement;
            }
        }
        return {};
    }
} // modelSpace