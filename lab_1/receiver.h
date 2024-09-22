//
// Created by anton on 9/12/24.
//

#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <set>
#include <string>
#include <boost/asio.hpp>

#include "sender.h"
#include "boost/bind.hpp"



namespace multicast {

    class receiver
    {
    public:
        receiver(boost::asio::io_service& io_service, sender *my_sender,
            const boost::asio::ip::address& listen_address,
            const boost::asio::ip::address& multicast_address);

        void handle_receive_from(const boost::system::error_code& error,
            size_t bytes_recvd);
        void handle_timeout(const boost::system::error_code& error);
    private:
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint sender_endpoint_;
        const boost::asio::ip::address& my_address_;
        enum { max_length = 1024 };
        char data_[max_length]{};
        boost::asio::deadline_timer timer_;
        int lastBreak = 5;
        sender *my_sender_;
        std::set<boost::asio::ip::address> alive_ips;
    };

} // multicast

#endif //RECEIVER_H
