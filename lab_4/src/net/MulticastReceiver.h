//
// Created by anton on 12/12/24.
//

#ifndef MULTICASTRECEIVER_H
#define MULTICASTRECEIVER_H

#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "net/NetMember.h"
#include <memory>

#include "UDPNetworkEnd.h"

namespace netEngine
{
    class MulticastReceiver
    {
    public:
        MulticastReceiver(std::shared_ptr<NetMember> initMemberPtr,
                          boost::asio::io_service& io_service,
                          const boost::asio::ip::address& listen_address,
                          const boost::asio::ip::address& multicast_address, const short& multicast_port);

    private:
        void handle_receive_from(const boost::system::error_code& error,
                                 size_t bytes_recvd);

    private:
        std::shared_ptr<NetMember> netMemberPtr;
        boost::asio::ip::udp::socket recvSocket;
        boost::asio::ip::udp::endpoint senderEndpoint;
        unsigned char dataBuf[UDP_MAX_SIZE]{};
    };
} // netEngine

#endif //MULTICASTRECEIVER_H
