//
// Created by anton on 12/12/24.
//

#include "net/MulticastReceiver.h"

#include <utility>

namespace netEngine
{
    MulticastReceiver::MulticastReceiver(std::shared_ptr<NetMember> initMemberPtr, boost::asio::io_service& io_service,
                                         const boost::asio::ip::address& listen_address,
                                         const boost::asio::ip::address& multicast_address,
                                         const short& multicast_port) :
        recvSocket(io_service), netMemberPtr{std::move(initMemberPtr)}
    {
        boost::asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
        recvSocket.open(listen_endpoint.protocol());
        recvSocket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        recvSocket.bind(listen_endpoint);
        recvSocket.set_option(boost::asio::ip::multicast::join_group(multicast_address));

        recvSocket.async_receive_from(
            boost::asio::buffer(dataBuf, UDP_MAX_SIZE), senderEndpoint,
            boost::bind(&MulticastReceiver::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void MulticastReceiver::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
    {
        GameMessage msg;

        msg.ParseFromArray(dataBuf, UDP_MAX_SIZE);

        if (msg.has_announcement())
        {
            GameMessage_AnnouncementMsg annMsg = msg.announcement();
            netMemberPtr->processAnnouncement(annMsg);
        }
        else if (msg.has_discover())
        {
            netMemberPtr->processDiscover();
            GameMessage_DiscoverMsg disMsg = msg.discover();
        }

        recvSocket.async_receive_from(
            boost::asio::buffer(dataBuf, 4096), senderEndpoint,
            boost::bind(&MulticastReceiver::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
} // netEngine
