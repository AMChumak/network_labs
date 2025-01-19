#include "Launcher.h"

#include "EatStrategyStd.h"
#include "KillStrategyStd.h"
#include "StepStrategyStd.h"


namespace engine {
    void Launcher::launch()
    {
        config_keeper.read_from_file();
        game_field = std::make_shared<Field>(config_keeper.get_width(), config_keeper.get_height());
        game_snakes = std::make_shared<std::vector<Snake>>();
        game_food_distributor = std::make_shared<FoodDistributor>(game_field, game_snakes);
        players_list = std::make_shared<PlayersList>();
        commands_queue = std::make_shared<CommandsQueue>();
        command_executor = std::make_shared<CommandExecutor>(game_field, game_snakes, game_food_distributor, players_list);

        main_loop();
    }

    void Launcher::launch(const GameState& state, const GameConfig& config)
    {
        state_order = state.state_order();
        config_keeper.read_from_msg(config);
        game_field = std::make_shared<Field>(config_keeper.get_width(), config_keeper.get_height());
        game_snakes = std::make_shared<std::vector<Snake>>();
        game_food_distributor = std::make_shared<FoodDistributor>(game_field, game_snakes);
        players_list = std::make_shared<PlayersList>(state.players());
        commands_queue = std::make_shared<CommandsQueue>();
        command_executor = std::make_shared<CommandExecutor>(game_field, game_snakes, game_food_distributor, players_list);

        game_food_distributor->fill_food(state);

        for (auto snake : state.snakes())
        {
            game_snakes->emplace_back(snake, game_field);
        }

        main_loop();
    }

    int Launcher::add_player(const std::string& name, const int& score) const
    {
        return players_list->add_player(name, score);
    }

    void Launcher::add_creation_command(int player_id) const
    {
        commands_queue->add_command(std::make_shared<CommandCreate>());
    }

    void Launcher::add_turn_command(int player_id, Direction direction) const
    {
        commands_queue->add_command(std::make_shared<CommandTurn>(player_id, direction));
    }

    void Launcher::add_observer(const std::shared_ptr<PlayersListObserver>& observer) const
    {
        players_list->add_observer(observer);
    }

    void Launcher::remove_observer(const std::shared_ptr<PlayersListObserver>& observer) const
    {
        players_list->remove_observer(observer);
    }

    void Launcher::create_game_state()
    {
        std::lock_guard<std::mutex> lock{state_mutex};

        state.set_state_order(state_order);

        state.clear_snakes();
        state.clear_foods();
        state.clear_players();

        for (Snake &snake : game_snakes)
        {
            GameState_Snake *snake_state = state.add_snakes();
            *snake_state = snake.generate_state();
        }

        std::vector<Coord> foods = game_food_distributor->get_foods();
        for (Coord &food : foods)
        {
            GameState_Coord *coord = state.add_foods();
            coord->set_x(food.x);
            coord->set_y(food.y);
        }

        GamePlayers *players_state = state.mutable_players();
        *players_state = players_list->generate_state();
    }

    [[noreturn]] void Launcher::main_loop()
    {
        while (true)
        {
            //get commands
            auto &extracted_commands = commands_queue->get_extracted_commands();

            //turn
            command_executor->execute_action_commands(extracted_commands);

            //step
            StepStrategyStd step_strategy;
            step_strategy.step(game_snakes);

            //eat
            EatStrategyStd eat_strategy;
            eat_strategy.eat(game_snakes, game_food_distributor);

            //kill
            KillStrategyStd kill_strategy;
            kill_strategy.kill(game_snakes);

            //born
             command_executor->execute_creation_commands(extracted_commands);

            //generate food
            game_food_distributor->refill_food();

            //save state
            create_game_state();

            //increment state order
            ++state_order;

            //wait
            usleep(1000 * config_keeper.get_state_delay_ms());
        }
    }
} // engine