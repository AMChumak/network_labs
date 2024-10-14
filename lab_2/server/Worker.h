#ifndef WORKER_H
#define WORKER_H
#include <thread>
#include <boost/asio/ip/tcp.hpp>

#include "FileWriter.h"
#include "ServerWorkerI.h"

namespace tcpServer {

class Worker final: public ServerWorkerI{
public:
    explicit Worker(boost::asio::io_context &context);
    StatusE getStatus() override;
    void initWork() override;
    void recvFile();
    Worker * clone() override;
    ~Worker() override;
    tcp::acceptor accept(boost::asio::ip::tcp::acceptor acceptorObj) override;
    unsigned long long getRecievedNum() override;
    std::chrono::system_clock::time_point getStartTime() override;
    unsigned long long getFileLength() override;
    void setStatus(StatusE) override;
    std::string getEndpointAddressPort() override;
    std::chrono::system_clock::time_point getStopTime() override;

private:
    std::string socketComplexAddress;
    unsigned long long fileLength = 1;
    unsigned long long countRecievedBytes_ = 0;
    FileWriter writer_;
    tcp::socket socket_;
    boost::asio::io_context &context_;
    StatusE status_;
    std::thread *workerThread_ = nullptr;
    std::chrono::system_clock::time_point start, stop;
};

} // tcpServer

#endif //WORKER_H
