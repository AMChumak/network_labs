//
// Created by anton on 9/22/24.
//

#include "ConnectManager.h"
#include <iostream>

using namespace tcpClient;
using boost::asio::ip::tcp;

ConnectManager::ConnectManager(const std::string& address, int port) : socket_(context_)
{
    tcp::resolver resolver(context_);
    tcp::resolver::results_type endpoints = resolver.resolve(address, "daytime");

    //boost::asio::ip::address addr = boost::asio::ip::address::from_string(address);
    //boost::asio::ip::basic_endpoint<tcp>endpoint_{addr, static_cast<unsigned short>(port)};
    //socket_.connect(endpoint_);
    boost::asio::connect(socket_, endpoints);
}

ConnectManager::~ConnectManager()
{
    socket_.close();
}

size_t ConnectManager::readStream(char* buffer, std::size_t bufferLength)
{
    return socket_.read_some(boost::asio::buffer(buffer , bufferLength));
}

size_t ConnectManager::writeStream(const char* buffer, std::size_t bufferLength)
{
    return socket_.write_some(boost::asio::buffer(buffer, bufferLength));
}

void ConnectManager::shutdownWrite()
{
    socket_.shutdown(boost::asio::socket_base::shutdown_send);
}


