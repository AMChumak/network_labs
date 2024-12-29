//
// Created by anton on 12/12/24.
//

#ifndef MASTERSTATE_H
#define MASTERSTATE_H
#include <net/NetMemberState.h>

namespace netEngine
{
    class MasterState : public NetMemberStateI
    {
    public:
        void processSteer(GameMessage msg, address senderAddr, unsigned short senderPort,
                          std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
                          std::shared_ptr<gameEngine::Launcher> launcher) override;

        void processState(GameMessage msg, address senderAddr, unsigned short senderPort,
                          std::shared_ptr<ConnectionsList> connections,
                          std::shared_ptr<modelSpace::PlayersListState> playersListState,
                          std::shared_ptr<modelSpace::FieldState> fieldState, std::shared_ptr<UDPNetworkEnd> netEnd,
                          int myId) override;
        void processJoin(GameMessage msg, address senderAddr, unsigned short senderPort,
                         std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
                         std::shared_ptr<gameEngine::Launcher> launcher) override;
    };
} // netEngine

#endif //MASTERSTATE_H
