//
// Created by anton on 12/12/24.
//

#ifndef NORMALSTATE_H
#define NORMALSTATE_H
#include "NetMemberState.h"

namespace netEngine {

class NormalState : public NetMemberStateI {
public:
    void processSteer(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
        std::shared_ptr<Launcher> launcher) override;
};

} // netEngine

#endif //NORMALSTATE_H
