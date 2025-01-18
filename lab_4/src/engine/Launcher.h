//
// Created by anton on 12/12/24.
//

#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <memory>

#include "CommandsQueue.h"
#include "FoodDistributor.h"
#include "Player.h"
#include "Snake.h"

#include <boost/thread/thread.hpp>

namespace gameEngine {

class Launcher {
public:
    void launchGame();
    void launchGame(int width, int height, const GameState& state);

    void addSteerCommand(const GameMessage_SteerMsg&);
    int addPlayer(const std::string& name);
    void removePlayer(const int &id);

private:
    void gameEngineMain();

private:
    std::mutex launcherMtx;
    bool isLaunching = false;
    boost::thread gameEngineThread;
    std::shared_ptr<CommandExecutor> commandExecutor;
    std::shared_ptr<CommandsQueue> commandsQueue;
    std::shared_ptr<PlayersList> playersList;
    std::shared_ptr<std::vector<Snake>> gameSnakes;
    std::shared_ptr<FoodDistributor> gameFoodDistributor;
    std::shared_ptr<Field> gameField;
};

} // gameEngine

#endif //LAUNCHER_H
