//
// Created by anton on 9/12/24.
//

#include "sender.h"

#include <utility>

const short multicast_port = 30001;
const int max_message_count = 1;

using namespace multicast;

sender::sender(boost::asio::io_service& io_service,
            const boost::asio::ip::address& multicast_address,const boost::asio::ip::address& send_address)
          : my_service_(io_service), endpoint_(multicast_address, multicast_port),
            socket_(io_service, endpoint_.protocol()),
            timer_(io_service),
            message_count_(0)
{
    boost::asio::ip::udp::endpoint send_endpoint(
        send_address, multicast_port+1);
    socket_.bind(send_endpoint);
    boost::asio::ip::multicast::outbound_interface option;
    if (send_address.to_string().find(':') != -1)
    {
        boost::asio::ip::address_v6 addr = send_address.to_v6();
        option = boost::asio::ip::multicast::outbound_interface(addr.scope_id());
    } else
    {
        boost::asio::ip::address_v4 addr = send_address.to_v4();
        option = boost::asio::ip::multicast::outbound_interface(addr);
    }
    socket_.set_option(option);

    message_ = "test message";

}

void sender::send_message(std::string msg)
{
    message_ = std::move(msg);
    socket_.async_send_to(
        boost::asio::buffer(message_), endpoint_,
        boost::bind(&sender::handle_send_to, this,
          boost::asio::placeholders::error));
    my_service_.run_one();
}


void sender::handle_send_to(const boost::system::error_code& error)
{
}


void sender::handle_timeout(const boost::system::error_code& error)
{
    if (!error)
    {
        std::ostringstream os;
        os << "Message " << message_count_++;
        message_ = os.str();

        socket_.async_send_to(
            boost::asio::buffer(message_), endpoint_,
            boost::bind(&sender::handle_send_to, this,
              boost::asio::placeholders::error));
    }
}