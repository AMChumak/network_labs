//
// Created by anton on 12/12/24.
//

#ifndef DEPUTYSTATE_H
#define DEPUTYSTATE_H
#include "NetMemberState.h"

namespace netEngine {

class DeputyState : public NetMemberStateI {
public:
    void processSteer(GameMessage msg, address senderAddr, unsigned short senderPort, std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId, std::shared_ptr<gameEngine::Launcher> launcher) override;
};

} // netEngine

#endif //DEPUTYSTATE_H
