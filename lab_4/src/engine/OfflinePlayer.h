//
// Created by anton on 12/12/24.
//

#ifndef OFFLINEPLAYER_H
#define OFFLINEPLAYER_H
#include "model/FieldState.h"
#include "Player.h"
#include "model/PlayersListState.h"

using namespace modelSpace;
namespace gameEngine {

class OfflinePlayer : public Player {
public:
    OfflinePlayer(int iId, std::string name, int score, const std::shared_ptr<FieldState>& field_state_ptr,
        const std::shared_ptr<PlayersListState>& players_list_state_ptr);
    void showState(GameState state) override;
    void showCommandResult(GameMessage message) override;
    GamePlayer getDescription() override;

private:
    std::shared_ptr<FieldState> fieldStatePtr;
    std::shared_ptr<PlayersListState> playersListStatePtr;
};

} // gameEngine

#endif //OFFLINEPLAYER_H
