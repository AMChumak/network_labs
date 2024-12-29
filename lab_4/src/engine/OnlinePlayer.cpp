//
// Created by anton on 12/12/24.
//

#include "OnlinePlayer.h"

#include <net/NetMember.h>

namespace gameEngine {

    OnlinePlayer::OnlinePlayer(int iId, const std::string& iname, int score,
        const std::shared_ptr<netEngine::NetMember>& net_member_ptr)
        : Player(iId, iname, score),
          netMemberPtr(net_member_ptr)
    {
    }

    void OnlinePlayer::showState(GameState state)
    {
        //todo
    }

    void OnlinePlayer::showCommandResult(GameMessage message)
    {
        //todo
    }

    GamePlayer OnlinePlayer::getDescription()
    {
        GamePlayer pl;
        pl.set_name(getName());
        pl.set_id(getPlayerId());
        pl.set_score(score_);
        pl.set_ip_address(addr.to_string());
        pl.set_port(port);
        pl.set_role(connectionsListPtr->getNodeRole(addr, port));
        return pl;
    }
} // gameEngine