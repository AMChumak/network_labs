//
// Created by anton on 1/18/25.
//

#include "PlayersList.h"

namespace engine
{
    Player PlayersList::invalid_player{-1, "invalid_player", -1}; //is used as error return code

    PlayersList::PlayersList()
    {
    }

    /*!
     * @brief loads all players from game state
     * @param [in] players game state
     */
    PlayersList::PlayersList(const GamePlayers& players)
    {
        for (auto player : players.players())
        {
            this->players.emplace_back(player.id(), player.name(), player.score());
            ids_set.insert(player.id());
        }
    }

    /*!
     *
     * @return constant vector of all players
     */
    const std::vector<Player>& PlayersList::get_players() const
    {
        return players;
    }

    /*!
     * @brief gets player by id
     * @param [in] player_id
     * @return reference to player in success case, reference to invalid_player else
     */
    Player& PlayersList::get_player(const int player_id)
    {
        for (auto& player : players)
        {
            if (player.get_player_id() == player_id)
                return player;
        }
        return invalid_player;
    }

    /*!
     * @return new id if success, -1 else
     */
    int PlayersList::get_first_available_id() const
    {
        if (players.size() == INT_MAX)
            return -1;

        for (int i = 0; i < players.size() + 1; i++)
        {
            if (!ids_set.contains(i))
            {
                return i;
            }
        }
        return -1;
    }


    /*!
     * @brief adds new player in list
     * @param [in] i_name name of new player
     * @param [in] i_score initial score of new player
     * @return id of new player in success case, -1 else
     */
    int PlayersList::add_player(std::string i_name, int i_score)
    {
        int new_id = get_first_available_id();
        if (new_id == -1)
            return -1;

        players.emplace_back(new_id, i_name, i_score);
        ids_set.insert(new_id);
        return new_id;
    }


    /*!
     * @brief erases player from list by id, will do nothing if incorrect id
     * @param [in] player_id
     */
    void PlayersList::erase_player(int player_id)
    {
        for (auto player = players.begin(); player != players.end(); ++player)
        {
            if (player->get_player_id() == player_id)
            {
                players.erase(player);
                return;
            }
        }
    }

    /*!
     * @brief erases player from list by iterator
     * @param [in] iter
     * @return actual iterator
     */
    std::vector<Player>::const_iterator PlayersList::erase_player(const std::vector<Player>::const_iterator iter)
    {
        return players.erase(iter);
    }
} // engine
