//
// Created by anton on 12/12/24.
//

#include "Launcher.h"

namespace gameEngine
{
    Launcher::Launcher(std::shared_ptr<NetMember> netMemberI, std::shared_ptr<modelSpace::FieldState> fieldStateI,
        std::shared_ptr<modelSpace::PlayersListState> playersListStateI) :
    netMember{std::move(netMemberI)}, fieldStatePtr{std::move(fieldStateI)}, playersListStatePtr{std::move(playersListStatePtr)}
    {
    }

    void Launcher::launchGame()
    {
        std::lock_guard<std::mutex> lock(launcherMtx);

        //interrupt last thread
        if (isLaunching)
        {
            gameEngineThread.interrupt();
            isLaunching = false;
        }

        //prepare structures
        gameField = std::make_shared<Field>();
        gameSnakes = std::make_shared<std::vector<Snake>>();
        gameFoodDistributor = std::make_shared<FoodDistributor>(gameField, gameSnakes);
        playersList = std::make_shared<PlayersList>();
        commandExecutor= std::make_shared<CommandExecutor>(gameField, gameSnakes, gameFoodDistributor, playersList);
        commandsQueue = std::make_shared<CommandsQueue>();

        //todo по-хорошему здесь надо проверить исключения


        //launch thread
        gameEngineThread = boost::thread(gameEngineMain);
    }

    void Launcher::launchGame(int width, int height, const GameState& state, const std::vector<std::shared_ptr<Player>>& players)
    {
        std::lock_guard<std::mutex> lock(launcherMtx);

        //interrupt last thread
        if (isLaunching)
        {
            gameEngineThread.interrupt();
            isLaunching = false;
        }

        //prepare structures
        gameField = std::make_shared<Field>(width, height);
        gameSnakes = std::make_shared<std::vector<Snake>>();
        for (const auto &snake : state.snakes())
        {
            gameSnakes->emplace_back(snake);
        }
        gameFoodDistributor = std::make_shared<FoodDistributor>(gameField, gameSnakes, state);
        playersList = std::make_shared<PlayersList>();
        for (const auto& player : players)
        {
            playersList->addPlayer(player);
        }
        commandExecutor= std::make_shared<CommandExecutor>(gameField, gameSnakes, gameFoodDistributor, playersList);
        commandsQueue = std::make_shared<CommandsQueue>();
        //todo по-хорошему здесь надо проверить исключения

        //launch thread
        gameEngineThread = boost::thread(gameEngineMain);
    }

    void Launcher::gameEngineMain()
    {

    }


    void Launcher::addSteerCommand(GameMessage_SteerMsg)
    {
    }

    int Launcher::addUser()
    {

        return ;
    }

    int Launcher::addUser(address userAddr, unsigned short userPort)
    {

    }

    void Launcher::removeUser(const int& id)
    {
    }
} // gameEngine
