//
// Created by anton on 12/9/24.
//

#include "net/NetMember.h"

namespace netEngine
{
    void NetMember::processAnnouncement(const GameMessage_AnnouncementMsg& announcementMsg)
    {
        gamesListStatePtr->addNewGame(announcementMsg.games()[0]);
    }

    void NetMember::processDiscover()
    {
        GameMessage msg;
        GameMessage_DiscoverMsg discover_msg;
        msg.set_allocated_discover(&discover_msg);
        netEndPtr->send_message(msg, multicastAddress, multicastPort);
    }

    void NetMember::processGameMsg(const GameMessage& msg, const address& senderAddr, unsigned short senderPort)
    {
        //filter expired messages by sequence number of message
        int seq = msg.msg_seq();
        if (connectionsListPtr->getCurRecvSeq(senderAddr, senderPort) == -1 ||
            seq <= connectionsListPtr->getCurRecvSeq(senderAddr, senderPort))
            return;
        connectionsListPtr->setCurRecvSeq(senderAddr, senderPort, seq);


        if (msg.has_ping())
        {
            netState->processPing(msg, senderAddr, senderPort, connectionsListPtr, netEndPtr, playersListStatePtr->getMyId() );
        }
        else if (msg.has_steer())
        {
            netState->processSteer(msg, senderAddr, senderPort, connectionsListPtr, netEndPtr, playersListStatePtr->getMyId() ,launcherPtr);
        }
        else if (msg.has_state())
        {
            netState->processState();
        }
        else if (msg.has_join())
        {
            netState->processJoin();
        }
        else if (msg.has_error())
        {
            netState->processError();
        }
        else if (msg.has_role_change())
        {
            netState->processRoleChange();
        }
    }
} // NetEngine
