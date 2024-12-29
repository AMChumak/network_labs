//
// Created by anton on 12/6/24.
//

#ifndef BORNSTRATEGYSTD_H
#define BORNSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace gameEngine
{
    class BornStrategyStd : public BornStrategyI
    {
    public:
        bool born(const int& ownerId, std::shared_ptr<std::vector<Snake>> snakes,
                  std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field,
                  std::shared_ptr<FindPlaceStrategyI> findPlaceStrategy) override;
    };
} // gameEngine

#endif //BORNSTRATEGYSTD_H
