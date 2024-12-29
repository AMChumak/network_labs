//
// Created by anton on 12/13/24.
//

#include "NetMemberState.h"

namespace netEngine
{
    void NetMemberStateI::processPing(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId)
    {
        GameMessage_AckMsg ackMsg;
        GameMessage dataMsg;
        dataMsg.set_msg_seq(msg.msg_seq());
        dataMsg.set_allocated_ack(&ackMsg);
        dataMsg.set_sender_id(myId);
        dataMsg.set_receiver_id(connections->getId(senderAddr, senderPort));
        netEnd->send_message(dataMsg, senderAddr, senderPort);
    }

    void NetMemberStateI::processAck(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<modelSpace::PlayersListState> playersListState)
    {
        connections->setAckSeq(senderAddr, senderPort, msg.msg_seq());
        playersListState->setMyId(msg.receiver_id());
    }

    void NetMemberStateI::processState(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<modelSpace::PlayersListState> playersListState,
        std::shared_ptr<modelSpace::FieldState> fieldState, std::shared_ptr<UDPNetworkEnd> netEnd, int myId)
    {
        //update connections
        connections->setCurRecvSeq(senderAddr,senderPort, msg.msg_seq());

        //send acknowledge
        GameMessage_AckMsg ackMsgEntry;
        GameMessage ackMsg;
        ackMsg.set_msg_seq(msg.msg_seq());
        ackMsg.set_allocated_ack(&ackMsgEntry);
        ackMsg.set_sender_id(myId);
        ackMsg.set_receiver_id(connections->getId(senderAddr, senderPort));
        netEnd->send_message(ackMsg, senderAddr, senderPort);

        //set new state
        playersListState->generateList(msg.state().state().players(),senderAddr.to_string(), senderPort);
        fieldState->generateState(msg.state().state());

    }

    void NetMemberStateI::processJoin()
    {
    }
}
