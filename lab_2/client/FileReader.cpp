//
// Created by anton on 9/22/24.
//

#include "FileReader.h"

#include <iostream>
#include <boost/exception/exception.hpp>
#include <limits>

using namespace tcpClient;

FileReader::FileReader(const std::string& path) : path_(path)
{
    inputFile_ = std::ifstream(path, std::ios::binary);

    if (!inputFile_) {
        std::cerr << "Failed to open file for reading." << std::endl;
        throw std::invalid_argument("Failed to open file for reading.");
    }

    //find length of file
    inputFile_.ignore( std::numeric_limits<std::streamsize>::max());
    length_ = inputFile_.gcount();
    inputFile_.clear();
    inputFile_.seekg(0, std::ios_base::beg);
}

FileReader::~FileReader()
{
    inputFile_.close();
}

long FileReader::read(char* buffer, long bufferSize)
{
    if (inputFile_.eof())
    {
        return -1;
    }
    inputFile_.read(buffer, bufferSize);
    return inputFile_.gcount();
}

std::string FileReader::getPath()
{
    return path_;
}

unsigned long long FileReader::getLength() const
{
    return length_;
}
