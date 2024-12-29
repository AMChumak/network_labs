//
// Created by anton on 12/12/24.
//

#include "UDPNetworkEnd.h"

#include "NetMember.h"
#include <boost/asio/placeholders.hpp>
#include <boost/bind/bind.hpp>

namespace netEngine
{
    UDPNetworkEnd::UDPNetworkEnd(std::shared_ptr<NetMember> initMemberPtr, boost::asio::io_service& io_service,
                                 const boost::asio::ip::address& listen_address,
                                 const boost::asio::ip::address& multicast_address,
                                 const short& multicast_port):
        workSocket(io_service), endIOService{io_service}
    {
        boost::asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
        workSocket.open(listen_endpoint.protocol());
        workSocket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        workSocket.bind(listen_endpoint);


        workSocket.async_receive_from(
            boost::asio::buffer(dataRecvBuf, UDP_MAX_SIZE), senderEndpoint,
            boost::bind(&UDPNetworkEnd::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void UDPNetworkEnd::send_message(const GameMessage& msg, const boost::asio::ip::address& recvAddr,
                                     const unsigned short& recvPort)
    {
        msg.SerializeToString(&dataSendBuf);

        if (recvAddr.to_string().find(':') != std::string::npos)
        {
            workSocket.open(boost::asio::ip::udp::v6());
        }
        else
        {
            workSocket.open(boost::asio::ip::udp::v4());
        }

        workSocket.async_send_to(
                boost::asio::buffer(dataSendBuf), boost::asio::ip::udp::endpoint{recvAddr, recvPort},
                boost::bind(&UDPNetworkEnd::handle_send_to, this,
                            boost::asio::placeholders::error));
        endIOService.run_one();
    }

    void UDPNetworkEnd::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
    {
        GameMessage msg;
        msg.ParseFromArray(dataRecvBuf, UDP_MAX_SIZE);

        netMemberPtr->processGameMsg(msg, senderEndpoint.address(), senderEndpoint.port());

        workSocket.async_receive_from(
            boost::asio::buffer(dataRecvBuf, UDP_MAX_SIZE), senderEndpoint,
            boost::bind(&UDPNetworkEnd::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void UDPNetworkEnd::handle_send_to(const boost::system::error_code& error)
    {
    }
} // netEngine
