//
// Created by anton on 12/6/24.
//

#ifndef BORNSTRATEGYSTD_H
#define BORNSTRATEGYSTD_H
#include "MoveStrategies.h"

namespace engine
{
    class BornStrategyStd : public BornStrategyI
    {
    public:
        bool born(const int& owner_id, std::shared_ptr<std::vector<Snake>> snakes,
                  std::shared_ptr<FoodDistributor> food_distr, std::shared_ptr<Field> field,
                  std::shared_ptr<FindPlaceStrategyI> find_place_strategy) override;
    };
} // engine

#endif //BORNSTRATEGYSTD_H
