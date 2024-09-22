//
// Created by anton on 9/12/24.
//

#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"

namespace multicast {

    class sender
    {
    public:
        sender(boost::asio::io_service& io_service,
            const boost::asio::ip::address& multicast_address,const boost::asio::ip::address& send_address);


        void send_message(std::string msg);

        void handle_send_to(const boost::system::error_code& error);

        void handle_timeout(const boost::system::error_code& error);

    private:
        boost::asio::io_service& my_service_;
        boost::asio::ip::udp::endpoint endpoint_;
        boost::asio::ip::udp::socket socket_;
        boost::asio::deadline_timer timer_;
        int message_count_;
        std::string message_;
    };

} // multicast

#endif //SENDER_H
