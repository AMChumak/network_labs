//
// Created by anton on 9/22/24.
//

#ifndef CONNECTMANAGER_H
#define CONNECTMANAGER_H
#include <string>
#include <boost/asio.hpp>

namespace tcpClient
{
    class ConnectManager
    {
    public:
        ConnectManager(const std::string& address, int port);
        ~ConnectManager();
        //TODO great five
        size_t readStream(char* buffer, std::size_t bufferLength);
        size_t writeStream(const char* buffer, std::size_t bufferLength);
        void shutdownWrite();
        template <typename T>
        size_t readNumber(T *value);
        template <typename T>
        size_t writeNumber(T value);

    private:
        boost::asio::io_context context_;
        boost::asio::ip::tcp::socket socket_;
    };

    template <typename T>
    size_t ConnectManager::readNumber(T *value)
    {
        return boost::asio::read(socket_, boost::asio::buffer(value, sizeof(T)));
    }

    template <typename T>
    size_t ConnectManager::writeNumber(T value)
    {
        return boost::asio::write(socket_, boost::asio::buffer(&value, sizeof(T)));
    }
} // tcpClient

#endif //CONNECTMANAGER_H
