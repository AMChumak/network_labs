//
// Created by anton on 12/6/24.
//

#ifndef KILLSTRATEGYSTD_H
#define KILLSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace gameEngine {

class KillStrategyStd : public KillStrategyI{
    void kill(std::shared_ptr<std::vector<Snake>> snakes) override;
};

} // gameEngine

#endif //KILLSTRATEGYSTD_H
