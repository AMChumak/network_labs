#include "../../src/engine/PlayersList.h"
#include "../../src/proto/snakes.pb.h"
#include <gtest/gtest.h>

using namespace engine;

TEST(players_list_tests, add_player_test)
{
    PlayersList list;

    int player_id = list.add_player("test_player", 10);
    ASSERT_NE(player_id, -1);

    auto players = list.get_players();
    ASSERT_EQ(players.size(), 1);
    ASSERT_EQ(players.at(0).get_player_id(), player_id);
    ASSERT_EQ(players.at(0).get_name(), "test_player");
    ASSERT_EQ(players.at(0).score, 10);
}

TEST (players_list_tests, load_players_test)
{
    GamePlayers players_state;
    auto last_player = players_state.add_players();
    last_player->set_id(42);
    last_player->set_name("answer");
    last_player->set_score(0);

    last_player = players_state.add_players();
    last_player->set_id(43);
    last_player->set_name("answer+1");
    last_player->set_score(1);

    PlayersList list{players_state};

    auto players = list.get_players();
    ASSERT_EQ(players.size(), 2);
    ASSERT_EQ(players.at(0).get_player_id(), 42);
    ASSERT_EQ(players.at(0).get_name(), "answer");
    ASSERT_EQ(players.at(0).score, 0);
    ASSERT_EQ(players.at(1).get_player_id(), 43);
    ASSERT_EQ(players.at(1).get_name(), "answer+1");
    ASSERT_EQ(players.at(1).score, 1);
}


TEST (players_list_tests, success_get_test)
{
    PlayersList list;

    int player_id = list.add_player("test_player", 10);
    ASSERT_NE(player_id, -1);

    auto player = list.get_player(0);
    ASSERT_EQ(player.get_player_id(), player_id);
    ASSERT_EQ(player.get_name(), "test_player");
    ASSERT_EQ(player.score, 10);
}


TEST (players_list_tests, failed_get_test)
{
    PlayersList list;

    int player_id = list.add_player("test_player", 10);
    ASSERT_NE(player_id, -1);

    auto player = list.get_player(42);
    ASSERT_EQ(player.get_player_id(), PlayersList::invalid_player.get_player_id());
    ASSERT_EQ(player.get_name(), PlayersList::invalid_player.get_name());
    ASSERT_EQ(player.score, PlayersList::invalid_player.score);
}


TEST (players_list_tests, first_erase_player_test)
{
    GamePlayers players_state;
    auto last_player = players_state.add_players();
    last_player->set_id(42);
    last_player->set_name("answer");
    last_player->set_score(0);

    last_player = players_state.add_players();
    last_player->set_id(43);
    last_player->set_name("answer+1");
    last_player->set_score(1);

    PlayersList list{players_state};

    list.erase_player(43);

    auto players = list.get_players();
    ASSERT_EQ(players.size(), 1);
    ASSERT_EQ(players.at(0).get_player_id(), 42);
}

TEST (players_list_tests, second_erase_player_test)
{
    GamePlayers players_state;
    auto last_player = players_state.add_players();
    last_player->set_id(42);
    last_player->set_name("answer");
    last_player->set_score(0);

    last_player = players_state.add_players();
    last_player->set_id(43);
    last_player->set_name("answer+1");
    last_player->set_score(1);

    PlayersList list{players_state};
    auto players = list.get_players();
    list.erase_player(--players.end());
    players = list.get_players();
    ASSERT_EQ(players.size(), 1);
    ASSERT_EQ(players.at(0).get_player_id(), 42);
}