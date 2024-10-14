//
// Created by anton on 9/24/24.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "ConnectManager.h"
#include "FileReader.h"

namespace tcpClient {

class Client {
public:
    Client(ConnectManager *connectManager, FileReader *fileReader);
    void sendFile();

private:
    ConnectManager *connectManager_;
    FileReader *fileReader_;
};

} // tcpClient

#endif //CLIENT_H
