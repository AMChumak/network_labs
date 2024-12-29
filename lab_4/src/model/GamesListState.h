//
// Created by anton on 12/12/24.
//

#ifndef GAMESLISTSTATE_H
#define GAMESLISTSTATE_H
#include <string>
#include <vector>

#include "../snakes.pb.h"

namespace modelSpace {

class GamesListState {
public:
    void addNewGame(const GameAnnouncement &announcement);
    void clearList();
    std::vector<GameAnnouncement> getGames();
    GameAnnouncement getGameByName(const std::string& gameName);

private:
    std::mutex stateMtx;
    std::vector<GameAnnouncement> games;
};

} // modelSpace

#endif //GAMESLISTSTATE_H
