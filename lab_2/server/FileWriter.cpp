//
// Created by anton on 9/25/24.
//

#include "FileWriter.h"

#include <iostream>
#include <unistd.h>

using namespace tcpServer;

void FileWriter::createFile(const std::string& name)
{
    unsigned long const pointPos = name.rfind('.');

    if(name.find('/') == std::string::npos)
    {
        path_ = "./uploads/" + name;
    } else
    {
        path_ = "./uploads/substituent";
    }

    while (access(path_.c_str(), F_OK) != -1)
    {
        if(pointPos == -1)
        {
            path_ = path_ + "a";
        } else
        {
            path_.insert(10 + pointPos, "a"); //10 - length of './uploads/'
        }
    }

    outputFile_ = std::ofstream(path_, std::ios::binary);
}

void FileWriter::write(char* buffer, long bufferLength)
{
    outputFile_.write(buffer, bufferLength);
}

void FileWriter::closeFile()
{
    outputFile_.close();
}
