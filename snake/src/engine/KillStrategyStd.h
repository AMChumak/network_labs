//
// Created by anton on 12/6/24.
//

#ifndef KILLSTRATEGYSTD_H
#define KILLSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace engine
{
    class KillStrategyStd : public KillStrategyI
    {
    public:
        void kill(std::shared_ptr<std::vector<Snake>> snakes) override;
    };
} // engine

#endif //KILLSTRATEGYSTD_H
