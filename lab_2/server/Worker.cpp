#include "Worker.h"

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <iconv.h>
#include <cstring>
#include <stdexcept>
#include <chrono>

using namespace tcpServer;

Worker::Worker(boost::asio::io_context &context): socket_(context), context_(context), status_(initialized)
{
}

tcp::acceptor Worker::accept(tcp::acceptor acceptorObj)
{
    acceptorObj.accept(socket_);
    return acceptorObj;
}

unsigned long long Worker::getRecievedNum()
{
    return countRecievedBytes_;
}

std::chrono::system_clock::time_point Worker::getStartTime()
{
    return start;
}

unsigned long long Worker::getFileLength()
{
    return fileLength;
}

void Worker::setStatus(StatusE newStatus)
{
    status_= newStatus;
}

std::string Worker::getEndpointAddressPort()
{

    return socketComplexAddress;
}

std::chrono::system_clock::time_point Worker::getStopTime()
{
    return stop;
}

StatusE Worker::getStatus()
{
    return status_;
}

void Worker::initWork()
{
    status_ = inWork;
    start = std::chrono::system_clock::now();
    workerThread_ = new std::thread{&Worker::recvFile, this};
    socketComplexAddress =  socket_.remote_endpoint().address().to_string() + " : " + std::to_string(socket_.remote_endpoint().port());
}


std::string convert_utf8_to_ascii(const std::string& utf8_str) {
    // Open an iconv descriptor
    iconv_t cd = iconv_open("ASCII//TRANSLIT", "UTF-8");
    if (cd == (iconv_t)(-1)) {
        throw std::runtime_error("iconv_open failed");
    }

    // Allocate buffers for input and output
    size_t in_len = utf8_str.size();
    size_t out_len = in_len; // ASCII can be up to the same length as UTF-8
    char* in_buf = const_cast<char*>(utf8_str.c_str());
    char* out_buf = new char[out_len];
    char* out_buf_start = out_buf;
    // Perform the conversion
    size_t result = iconv(cd, &in_buf, &in_len, &out_buf, &out_len);
    if (result == (size_t)(-1)) {
        delete[] out_buf_start;
        iconv_close(cd);
        throw std::runtime_error("iconv conversion failed");
    }

    // Create the resulting string
    std::string ascii_str(out_buf_start, out_buf - out_buf_start);

    // Clean up
    delete[] out_buf_start;
    iconv_close(cd);

    return ascii_str;
}

void Worker::recvFile()
{
    //get Name length
    unsigned short nameLength;
    boost::asio::read(socket_, boost::asio::buffer(&nameLength, sizeof(unsigned short)));

    //get Name in UTF-8 encoding
    char* buff = new char[nameLength + 1];
    boost::asio::read(socket_, boost::asio::buffer(buff, sizeof(char) * nameLength));
    buff[nameLength] = 0;
    std::string utfName{buff};

    //decode name
    std::string name = convert_utf8_to_ascii(utfName);

    //create file
    writer_.createFile(name);
    delete[] buff;

    //get file name

    boost::asio::read(socket_, boost::asio::buffer(&fileLength, sizeof(unsigned long long)));

    //read file while can
    char *fileCopyBuff = new char[4096];
    boost::asio::mutable_buffer fileBuff = boost::asio::buffer(fileCopyBuff, sizeof(char) * 4096);
    boost::system::error_code error;
    while (error != boost::asio::error::eof  && countRecievedBytes_ < fileLength )
    {
        std::size_t length = boost::asio::read(socket_, fileBuff, error);
        writer_.write(fileCopyBuff, length);
        countRecievedBytes_ += length;
    }
    stop = std::chrono::system_clock::now();
    writer_.closeFile();

    //send count bytes to client
    boost::asio::write(socket_, boost::asio::buffer(&countRecievedBytes_, sizeof(unsigned long long)));

    //free resources
    delete[] fileCopyBuff;
    socket_.close();

    //change status for manager
    if (fileLength == countRecievedBytes_)
    {
        status_ = stoppedSuccessful;
    } else
    {
        status_ = stoppedFailed;
    }
}

Worker* Worker::clone()
{
    return new Worker{context_};
}

Worker::~Worker()
{
    workerThread_->join();
}


