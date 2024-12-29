//
// Created by anton on 12/12/24.
//

#ifndef VIEWERSTATE_H
#define VIEWERSTATE_H
#include "NetMemberState.h"

namespace netEngine {

class ViewerState : public NetMemberStateI{
public:
    void processSteer(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
        std::shared_ptr<Launcher> launcher) override;
};

} // netEngine

#endif //VIEWERSTATE_H
