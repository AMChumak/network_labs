//
// Created by anton on 12/12/24.
//

#include "Launcher.h"

namespace gameEngine
{
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

    void Launcher::launchGame(int width, int height, const GameState& state)
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
        playersList = std::make_shared<PlayersList>(state.players().players());
        commandExecutor= std::make_shared<CommandExecutor>(gameField, gameSnakes, gameFoodDistributor, playersList);
        commandsQueue = std::make_shared<CommandsQueue>();
        //todo по-хорошему здесь надо проверить исключения

        //launch thread
        gameEngineThread = boost::thread(gameEngineMain);
    }

    void Launcher::gameEngineMain()
    {

    }
    
    void Launcher::addSteerCommand(const GameMessage_SteerMsg& msg)
    {
        Direction direction =  convertNetToEngineDirection(msg.direction());
        CommandTurn turn;
        turn.direction = direction;
        commandsQueue->addCommand(turn);
    }

    int Launcher::addPlayer(const std::string& name)
    {
        int newPlayerId = playersList->addPlayer(name);
        commandsQueue->addCommand()
        return newPlayerId;
    }

    void Launcher::removePlayer(const int& id)
    {
        playersList->removePlayer(id);
    }
} // gameEngine
