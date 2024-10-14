//
// Created by anton on 9/24/24.
//

#ifndef PROTOCOLSTRATEGY_H
#define PROTOCOLSTRATEGY_H

namespace tcpClient {

class ProtocolStrategy {
public:
    virtual ~ProtocolStrategy() = default;
    virtual void sendFile() = 0;
    virtual bool check() = 0;
};

} // tcpClient

#endif //PROTOCOLSTRATEGY_H
