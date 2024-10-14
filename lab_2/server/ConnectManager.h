//
// Created by anton on 9/25/24.
//

#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "ServerWorkerI.h"

namespace tcpServer
{
    class ConnectManager final
    {
    public:
        explicit ConnectManager(int port, ServerWorkerI* workerPrototype);
        ~ConnectManager();
        //todo great five
        void handleConnects();

        void checkSpeed();

        int isTerminated = 0;
    private:
        boost::asio::io_context context_;
        tcp::acceptor acceptor_;
        ServerWorkerI *prototype_;
        std::vector<std::pair<ServerWorkerI *, unsigned long long>> workers_;
    };
} // tcpServer

#endif //SOCKETMANAGER_H
