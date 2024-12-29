//
// Created by anton on 12/12/24.
//

#include "MasterState.h"

#include <boost/asio/ip/address.hpp>

#include "ConnectionsList.h"
#include "snakes.pb.h"
#include "UDPNetworkEnd.h"
#include "engine/Launcher.h"

namespace netEngine {
    void MasterState::processSteer(GameMessage msg, boost::asio::ip::address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
        std::shared_ptr<gameEngine::Launcher> launcher)
    {
        //send acknowledge
        GameMessage_AckMsg ackMsg;
        GameMessage dataMsg;
        dataMsg.set_msg_seq(msg.msg_seq());
        dataMsg.set_allocated_ack(&ackMsg);
        dataMsg.set_sender_id(myId);
        dataMsg.set_receiver_id(connections->getId(senderAddr, senderPort));
        netEnd->send_message(dataMsg, senderAddr, senderPort);

        //add command in queue
        launcher->addSteerCommand(msg.steer());
    }

    void MasterState::processState(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<modelSpace::PlayersListState> playersListState,
        std::shared_ptr<modelSpace::FieldState> fieldState, std::shared_ptr<UDPNetworkEnd> netEnd, int myId)
    {
        //todo возможно надо отправлять сообщение об ошибке
    }

    void MasterState::processJoin(GameMessage msg, address senderAddr, unsigned short senderPort,
        std::shared_ptr<ConnectionsList> connections, std::shared_ptr<UDPNetworkEnd> netEnd, int myId,
        std::shared_ptr<gameEngine::Launcher> launcher)
    {
        launcher->addUser(senderAddr, senderPort);
    }
} // netEngine