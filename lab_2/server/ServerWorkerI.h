//
// Created by anton on 9/25/24.
//

#ifndef WORKERI_H
#define WORKERI_H
#include <boost/asio/ip/tcp.hpp>
using boost::asio::ip::tcp;

namespace tcpServer
{
    enum StatusE
    {
        initialized = 0,
        inWork = 1,
        stoppedSuccessful = 2,
        stoppedFailed = 3,
        read = 4
    };

    class ServerWorkerI
    {
    public:
        virtual tcp::acceptor accept(boost::asio::ip::tcp::acceptor acceptorObj) = 0;
        virtual StatusE getStatus() = 0;
        virtual void setStatus(StatusE)=0;
        virtual unsigned long long getRecievedNum() = 0;
        virtual unsigned long long getFileLength() = 0;
        virtual std::string getEndpointAddressPort() = 0;
        virtual std::chrono::system_clock::time_point getStartTime() = 0;
        virtual std::chrono::system_clock::time_point getStopTime() = 0;
        virtual void initWork() = 0;
        virtual ServerWorkerI* clone() = 0;
        virtual ~ServerWorkerI() = default;
    };
}

#endif //WORKERI_H
