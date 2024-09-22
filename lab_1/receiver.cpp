//
// Created by anton on 9/12/24.
//
const short multicast_port = 30001;
#include "receiver.h"

using namespace multicast;

receiver::receiver(boost::asio::io_service& io_service, sender* my_sender,
                   const boost::asio::ip::address& listen_address,
                   const boost::asio::ip::address& multicast_address)
    : socket_(io_service), timer_(io_service), my_sender_(my_sender), my_address_(listen_address)
{
    // Create the socket so that multiple may be bound to the same address.
    boost::asio::ip::udp::endpoint listen_endpoint(
        listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    boost::asio::ip::multicast::outbound_interface option;
    if (listen_address.to_string().find(':') != -1)
    {
        boost::asio::ip::address_v6 addr = listen_address.to_v6();
        option = boost::asio::ip::multicast::outbound_interface(addr.scope_id());
    } else
    {
        boost::asio::ip::address_v4 addr = listen_address.to_v4();
        option = boost::asio::ip::multicast::outbound_interface(addr);
    }
    socket_.set_option(option);


    // Join the multicast group.
    socket_.set_option(
        boost::asio::ip::multicast::join_group(multicast_address));

    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        boost::bind(&receiver::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    timer_.expires_from_now(boost::posix_time::seconds(0));
    timer_.async_wait(
        boost::bind(&receiver::handle_timeout, this,
                    boost::asio::placeholders::error));
}

void receiver::handle_receive_from(const boost::system::error_code& error,
                                   size_t bytes_recvd)
{
    if (!error)
    {
        std::string msg(data_, bytes_recvd);
        if (msg == "anybody?")
        {
            my_sender_->send_message("hello");
        }
        else if (msg == "hello")
        {
            alive_ips.insert(sender_endpoint_.address());
        }
        else if (msg == "bye")
        {
            alive_ips.erase(sender_endpoint_.address());
        }


        socket_.async_receive_from(
            boost::asio::buffer(data_, max_length), sender_endpoint_,
            boost::bind(&receiver::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}

void receiver::handle_timeout(const boost::system::error_code& error)
{
    if (!error)
    {
        if (lastBreak == 5)
        {
            alive_ips.clear();
            my_sender_->send_message("anybody?");
            lastBreak = 1;
            timer_.expires_from_now(boost::posix_time::seconds(1));
        }
        else
        {
            std::system ("clear");
            std::cout << "alive:" << std::endl;
            for (auto el : alive_ips)
            {
                std::cout << el.to_string() << std::endl;
            }
            std::cout << std::endl << std::endl;
            lastBreak = 5;
            timer_.expires_from_now(boost::posix_time::seconds(0));
        }

        timer_.async_wait(
            boost::bind(&receiver::handle_timeout, this,
                        boost::asio::placeholders::error));
    }
}
