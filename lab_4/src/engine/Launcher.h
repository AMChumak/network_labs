//
// Created by anton on 12/12/24.
//

#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <memory>
#include "net/NetMember.h"

#include "CommandsQueue.h"
#include "FoodDistributor.h"
#include "Player.h"
#include "Snake.h"

#include <boost/thread/thread.hpp>

namespace gameEngine {

class Launcher {
public:
    Launcher(std::shared_ptr<NetMember> netMemberI, std::shared_ptr<modelSpace::FieldState> fieldStateI, std::shared_ptr<modelSpace::PlayersListState> playersListStateI);
    void launchGame();
    void launchGame(int width, int height, const GameState& state, const std::vector<std::shared_ptr<Player>>& players);

    void addSteerCommand(GameMessage_SteerMsg);
    void addUser();
    void addUser(address userAddr, unsigned short userPort);
    void removeUser(const int &id);

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

    std::shared_ptr<netEngine::NetMember> netMember;

    std::shared_ptr<modelSpace::FieldState> fieldStatePtr;
    std::shared_ptr<modelSpace::PlayersListState> playersListStatePtr;
};

} // gameEngine

#endif //LAUNCHER_H
