#include <iostream>
#include "receiver.h"
#include "sender.h"
#include <boost/thread.hpp>

using namespace multicast;

boost::asio::io_service service[2];




int main(int argc, char* argv[])
{
    boost::asio::io_service serviceS;
    sender s(service[0], boost::asio::ip::address::from_string(argv[1]), boost::asio::ip::address::from_string(argv[2]));
    receiver r(service[1], &s,
        boost::asio::ip::address::from_string(argv[2]),
        boost::asio::ip::address::from_string(argv[1]));
    service[1].run();

    int i = 0;
    std::cin >> i;

    return 0;
}


