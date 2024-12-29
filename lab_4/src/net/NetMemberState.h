//
// Created by anton on 12/9/24.
//

#ifndef NETMEMBERSTATE_H
#define NETMEMBERSTATE_H
#include "ConnectionsList.h"
#include "engine/Launcher.h"
#include "UDPNetworkEnd.h"
#include "model/PlayersListState.h"

namespace netEngine
{
    class NetMemberStateI
    {
    public:
        virtual ~NetMemberStateI() = default;
        virtual void processPing(GameMessage msg, address senderAddr, unsigned short senderPort,
                                 std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd,
                                 int myId);
        virtual void processSteer(GameMessage msg, address senderAddr, unsigned short senderPort,
                                  std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd,
                                  int myId, std::shared_ptr<gameEngine::Launcher> launcher) =0;
        virtual void processAck(GameMessage msg, address senderAddr, unsigned short senderPort,
                                std::shared_ptr<ConnectionsList> connections,
                                std::shared_ptr<modelSpace::PlayersListState> playersListState);
        virtual void processState(GameMessage msg, address senderAddr, unsigned short senderPort,
                                  std::shared_ptr<ConnectionsList> connections,
                                  std::shared_ptr<modelSpace::PlayersListState> playersListState,
                                  std::shared_ptr<modelSpace::FieldState> fieldState,
                                  std::shared_ptr<UDPNetworkEnd> netEnd, int myId);
        virtual void processJoin(GameMessage msg, address senderAddr, unsigned short senderPort,
                                 std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd,
                                 int myId,
                                 std::shared_ptr<gameEngine::Launcher> launcher);
        virtual void processError();
        virtual void processRoleChange();
    };
} // netEngine

#endif //NETMEMBERSTATE_H
