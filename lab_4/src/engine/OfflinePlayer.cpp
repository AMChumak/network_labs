//
// Created by anton on 12/12/24.
//

#include "OfflinePlayer.h"

#include <utility>

namespace gameEngine {

    OfflinePlayer::OfflinePlayer(int iId, std::string name, int score, const std::shared_ptr<FieldState>& field_state_ptr,
        const std::shared_ptr<PlayersListState>& players_list_state_ptr)
        : Player(iId, std::move(name), score),
          fieldStatePtr(field_state_ptr),
          playersListStatePtr(players_list_state_ptr)
    {
    }

    void OfflinePlayer::showState(GameState state)
    {
        fieldStatePtr->generateState(state);
        playersListStatePtr->generateList(state.players());
    }

    void OfflinePlayer::showCommandResult(GameMessage message)
    {
    }

    GamePlayer OfflinePlayer::getDescription()
    {
        GamePlayer pl;
        pl.set_name(getName());
        pl.set_id(getPlayerId());
        pl.set_role(MASTER);
        pl.set_score(score_);
        return pl;
    }
} // gameEngine