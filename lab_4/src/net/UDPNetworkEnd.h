//
// Created by anton on 12/12/24.
//

#ifndef UDPNETWORKEND_H
#define UDPNETWORKEND_H
#include <memory>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>

#include "../snakes.pb.h"

namespace netEngine
{
    inline int UDP_MAX_SIZE = 4096;

    class NetMember;

    class UDPNetworkEnd
    {
    public:
        UDPNetworkEnd(std::shared_ptr<NetMember> initMemberPtr,
                      boost::asio::io_service& io_service,
                      const boost::asio::ip::address& listen_address,
                      const boost::asio::ip::address& multicast_address, const short& multicast_port);

        void send_message(const GameMessage &msg,const boost::asio::ip::address &recvAddr, const unsigned short &recvPort);


    private:
        void handle_receive_from(const boost::system::error_code& error,
                                 size_t bytes_recvd);

        void handle_send_to(const boost::system::error_code& error);

    private:
        boost::asio::io_service& endIOService;
        std::shared_ptr<NetMember> netMemberPtr;
        boost::asio::ip::udp::socket workSocket;
        boost::asio::ip::udp::endpoint senderEndpoint;
        unsigned char dataRecvBuf[UDP_MAX_SIZE];
        std::string dataSendBuf;
    };
} // netEngine

#endif //UDPNETWORKEND_H
