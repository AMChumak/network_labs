//
// Created by anton on 12/9/24.
//

#ifndef NETMEMBER_H
#define NETMEMBER_H

#include "ConnectionsList.h"
#include "model/FieldState.h"
#include "model/GamesListState.h"
#include "NetMemberState.h"
#include "model/PlayersListState.h"
#include "snakes.pb.h"
#include "UDPNetworkEnd.h"
#include "ViewerState.h"

namespace netEngine {

    inline boost::asio::ip::address multicastAddress = boost::asio::ip::address::from_string("239.192.0.4");
    const unsigned short multicastPort = 9192;


class NetMember {
public:


    void processAnnouncement(const GameMessage_AnnouncementMsg &announcementMsg);
    void processDiscover();
    void processGameMsg(const GameMessage &msg, const address& senderAddr, unsigned short senderPort);

    void sendStateMsg(GameMessage &msg);

    void setNetMemberState(std::shared_ptr<NetMemberStateI> newState);

private:
    int seq = 0;
    GameState gameState;

    std::unique_ptr<NetMemberStateI> netState;
    std::shared_ptr<ConnectionsList> connectionsListPtr;
    std::shared_ptr<UDPNetworkEnd> netEndPtr;

    std::shared_ptr<modelSpace::FieldState> fieldStatePtr;
    std::shared_ptr<modelSpace::PlayersListState> playersListStatePtr;
    std::shared_ptr<modelSpace::GamesListState> gamesListStatePtr;

    std::shared_ptr<Launcher> launcherPtr;
};

} // NetEngine

#endif //NETMEMBER_H
