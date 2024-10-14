//
// Created by anton on 9/24/24.
//

#include "Client.h"
#include <iconv.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

using namespace tcpClient;

Client::Client(ConnectManager* connectManager, FileReader* fileReader): connectManager_(connectManager), fileReader_(fileReader)
{
}


std::string convert_ascii_to_utf8(const std::string& ascii_str) {
    // Open an iconv descriptor
    iconv_t cd = iconv_open("UTF-8", "ASCII");
    if (cd == (iconv_t)(-1)) {
        throw std::runtime_error("iconv_open failed");
    }

    // Allocate buffers for input and output
    size_t in_len = ascii_str.size();
    size_t out_len = in_len * 4; // UTF-8 can be up to 4 bytes per character
    char* in_buf = const_cast<char*>(ascii_str.c_str());
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
    std::string utf8_str(out_buf_start, out_buf - out_buf_start);

    // Clean up
    delete[] out_buf_start;
    iconv_close(cd);

    return utf8_str;
}


void Client::sendFile()
{
    //create file name
    std::string name = fileReader_->getPath();
    auto lastSlash = fileReader_->getPath().rfind('/');
    if (lastSlash != std::basic_string<char>::npos)
    {
        name = name.substr(lastSlash + 1);
    }
    std::string utfName = convert_ascii_to_utf8(name);
    //send file name length
    connectManager_->writeNumber(static_cast<unsigned short>(strlen(utfName.c_str())));
    //send file name
    connectManager_->writeStream(utfName.c_str(), strlen(utfName.c_str()));

    //send file length
    connectManager_->writeNumber(static_cast<unsigned long long>(fileReader_->getLength()));
    std::cout<<fileReader_->getLength()<<" expected"<<std::endl;
    //send file
    const auto fileCopyBuff = new char[4096];
    long readedCount = 0;
    while ((readedCount = fileReader_->read(fileCopyBuff, 4096)) != -1)
    {
        connectManager_->writeStream(fileCopyBuff, readedCount);
        sleep(1);
    }
    connectManager_->shutdownWrite();


    //check answer
    unsigned long long checkLength = 0;
    connectManager_->readNumber(&checkLength);
    std::cout<<checkLength<<" reached"<< std::endl;
    //free resources
    delete[] fileCopyBuff;
}