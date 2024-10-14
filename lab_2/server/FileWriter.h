//
// Created by anton on 9/25/24.
//

#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <fstream>
#include <string>

namespace tcpServer {

class FileWriter {
public:
    void createFile(const std::string& name);
    void write(char *buffer, long bufferLength);
    void closeFile();
private:
    std::ofstream outputFile_;
    std::string path_;
};

} // tcpServer

#endif //FILEWRITER_H
