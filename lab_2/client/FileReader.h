//
// Created by anton on 9/22/24.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <string>

namespace tcpClient
{
    class FileReader
    {
    public:
        explicit FileReader(const std::string& path) noexcept(false);
        ~FileReader();
        //todo great five

        long read(char* buffer, long bufferSize);

        std::string getPath();
        unsigned long long getLength() const;
    private:
        std::ifstream inputFile_;
        std::string path_;
        unsigned long long length_=0;
    };
} // tcpClient

#endif //FILEREADER_H
