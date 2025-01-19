#include <fstream>

#include "../../src/engine/ConfigKeeper.h"
#include <gtest/gtest.h>

using namespace engine;


TEST(config_keeper_tests, read_from_file_test)
{
    if (std::ofstream conf_file{"snakes.conf"}; conf_file.is_open())
    {
        conf_file << "width = " << 10 << std::endl;
        conf_file << "height = " << 10 << std::endl;
        conf_file << "food_static = " << 12 << std::endl;
        conf_file << "state_delay_ms = " << 1000 << std::endl;
        conf_file.close();
    }

    ConfigKeeper config_keeper;

    config_keeper.read_from_file();
    ASSERT_EQ(config_keeper.get_width(), 10);
    ASSERT_EQ(config_keeper.get_height(), 10);
    ASSERT_EQ(config_keeper.get_food_static(), 12);
    ASSERT_EQ(config_keeper.get_state_delay_ms(), 1000);
}

TEST(config_keeper_tests, write_to_file_test)
{
    ConfigKeeper config_keeper;
    config_keeper.write_to_file();

    config_keeper.read_from_file();
    ASSERT_EQ(config_keeper.get_width(), 40);
    ASSERT_EQ(config_keeper.get_height(), 30);
    ASSERT_EQ(config_keeper.get_food_static(), 1);
    ASSERT_EQ(config_keeper.get_state_delay_ms(), 1000);
}

TEST (config_keeper_tests, read_from_game_state_test)
{
    ConfigKeeper config_keeper;

    GameConfig config;
    config.set_width(10);
    config.set_height(10);
    config.set_food_static(12);
    config.set_state_delay_ms(1000);

    config_keeper.read_from_msg(config);

    ASSERT_EQ(config_keeper.get_width(), 10);
    ASSERT_EQ(config_keeper.get_height(), 10);
    ASSERT_EQ(config_keeper.get_food_static(), 12);
    ASSERT_EQ(config_keeper.get_state_delay_ms(), 1000);
}