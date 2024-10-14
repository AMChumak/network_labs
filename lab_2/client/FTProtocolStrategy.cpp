//
// Created by anton on 9/24/24.
//

#include "FTProtocolStrategy.h"

using namespace tcpClient;


FTProtocolStrategy::FTProtocolStrategy(ConnectManager* manager, FileReader* fileReader) : connectManager_(manager),
    fileReader_(fileReader)
{
}

FTProtocolStrategy::~FTProtocolStrategy()
= default;

void FTProtocolStrategy::sendFile()
{


}

bool FTProtocolStrategy::check()
{
}
