//
// Created by anton on 9/24/24.
//

#ifndef FTPROTOCOLSTRATEGY_H
#define FTPROTOCOLSTRATEGY_H
#include "ConnectManager.h"
#include "FileReader.h"
#include "ProtocolStrategy.h"

namespace tcpClient {

class FTProtocolStrategy final: public ProtocolStrategy {
    FTProtocolStrategy(ConnectManager *manager, FileReader *fileReader);
    ~FTProtocolStrategy() override;
    void sendFile() override;
    bool check() override;

private:
    ConnectManager *connectManager_;
    FileReader *fileReader_;
};

} // tcpClient

#endif //FTPROTOCOLSTRATEGY_H
