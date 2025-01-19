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

TEST(players_list_tests, load_players_test)
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


TEST(players_list_tests, success_get_test)
{
    PlayersList list;

    int player_id = list.add_player("test_player", 10);
    ASSERT_NE(player_id, -1);

    auto player = list.get_player(0);
    ASSERT_EQ(player.get_player_id(), player_id);
    ASSERT_EQ(player.get_name(), "test_player");
    ASSERT_EQ(player.score, 10);
}


TEST(players_list_tests, failed_get_test)
{
    PlayersList list;

    int player_id = list.add_player("test_player", 10);
    ASSERT_NE(player_id, -1);

    auto player = list.get_player(42);
    ASSERT_EQ(player.get_player_id(), PlayersList::invalid_player.get_player_id());
    ASSERT_EQ(player.get_name(), PlayersList::invalid_player.get_name());
    ASSERT_EQ(player.score, PlayersList::invalid_player.score);
}


TEST(players_list_tests, first_erase_player_test)
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

    auto &players = list.get_players();
    ASSERT_EQ(players.size(), 1);
    ASSERT_EQ(players.at(0).get_player_id(), 42);
}

TEST(players_list_tests, second_erase_player_test)
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
    auto &players = list.get_players();
    list.erase_player(--players.end());
    ASSERT_EQ(players.size(), 1);
    ASSERT_EQ(players.at(0).get_player_id(), 42);
}


class PlayersObserver : public PlayersListObserver
{
public:
    int get_last_deleted_player_id() const
    {
        return last_id;
    }
    void on_player_delete(int player_id) override
    {
        last_id = player_id;
    }
private:
    int last_id = -2;
};

TEST(players_list_tests, add_players_observer_test)
{
    std::shared_ptr<PlayersObserver> observer = std::make_shared<PlayersObserver>();
    PlayersList list;
    list.add_observer(observer);
    int player_id = list.add_player("test_player", 10);
    list.erase_player(player_id);
    int last = observer->get_last_deleted_player_id();
    ASSERT_EQ(last, player_id);
}

TEST(players_list_tests, remove_players_observer_test)
{
    std::shared_ptr<PlayersObserver> observer = std::make_shared<PlayersObserver>();
    PlayersList list;
    list.add_observer(observer);
    list.remove_observer(observer);
    int player_id = list.add_player("test_player", 10);
    list.erase_player(player_id);
    int last = observer->get_last_deleted_player_id();
    ASSERT_EQ(last, -2);
}
