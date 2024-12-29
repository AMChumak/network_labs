//
// Created by anton on 12/12/24.
//

#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H
#include "net/NetMember.h"

#include "net/ConnectionsList.h"
#include "Player.h"

namespace gameEngine {

class OnlinePlayer : public Player{
public:
    OnlinePlayer(int iId, const std::string& iname, int score,
                 const std::shared_ptr<netEngine::NetMember>& net_member_ptr);
    void showState(GameState state) override;
    void showCommandResult(GameMessage message) override;
    GamePlayer getDescription() override;


private:
    boost::asio::ip::address addr;
    unsigned short port;
    std::shared_ptr<netEngine::NetMember> netMemberPtr;
    std::shared_ptr<netEngine::ConnectionsList> connectionsListPtr;
};

} // gameEngine

#endif //ONLINEPLAYER_H
