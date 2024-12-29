//
// Created by anton on 12/12/24.
//

#ifndef CONNECTIONSLIST_H
#define CONNECTIONSLIST_H
#include <string>
#include <boost/asio.hpp>
#include "snakes.pb.h"
#include <memory>

using namespace boost::asio::ip;

namespace netEngine
{
    struct NodeDescription
    {
        int playerId;
        address nodeAddr;
        unsigned short nodePort;
        NodeRole nodeRole;
        int lastSentMsgSeq, curSentSeq, lastRecvSeq, curRecvSeq, ackSeq;
    };

    class ConnectionsList
    {
    public:
        ConnectionsList();

        void addConnect(NodeDescription description);
        void removeConnect(address delAddr, unsigned short delPort);


        //geters and setters for fields of NodeDescription
        int getId(address targetAddr, unsigned short targetPort);
        void setId(address targetAddr, unsigned short targetPort, int newId);
        NodeRole getNodeRole(address targetAddr, unsigned short targetPort);
        void setNodeRole(address targetAddr, unsigned short targetPort, NodeRole newRole);
        int getLastSentSeq(address targetAddr, unsigned short targetPort);
        void setLastSentSeq(address targetAddr, unsigned short targetPort, int newLastSentSeq);
        int getCurSentSeq(address targetAddr, unsigned short targetPort);
        void setCurSentSeq(address targetAddr, unsigned short targetPort, int newCurSentSeq);
        int getLastRecvSeq(address targetAddr, unsigned short targetPort);
        void setLastRecvSeq(address targetAddr, unsigned short targetPort, int newLastRecvSeq);
        int getCurRecvSeq(address targetAddr, unsigned short targetPort);
        void setCurRecvSeq(address targetAddr, unsigned short targetPort, int newCurRecvSeq);
        int getAckSeq(address targetAddr, unsigned short targetPort);
        void setAckSeq(address targetAddr, unsigned short targetPort, int newAckSeq);

    private:
        std::mutex listMtx;
        std::vector<NodeDescription> connections;
    };
} // netEngine

#endif //CONNECTIONSLIST_H
