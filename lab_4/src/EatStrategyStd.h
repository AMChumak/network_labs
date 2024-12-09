//
// Created by anton on 12/5/24.
//

#ifndef EATSTRATEGYSTD_H
#define EATSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace gameEngine {

class EatStrategyStd : public EatStrategyI{
public:
    void eat(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> foodDistr) override;
};

} // gameEngine

#endif //EATSTRATEGYSTD_H
