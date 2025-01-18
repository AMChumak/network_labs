//
// Created by anton on 12/6/24.
//

#ifndef FINDPLACESTRATEGYSTD_H
#define FINDPLACESTRATEGYSTD_H
#include "MoveStrategies.h"

namespace engine {

class FindPlaceStrategyStd : public FindPlaceStrategyI{
public:
    //returns pair with coord: -1 ,-1 if not found
    CoordDirectionPair find_place(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> food_distr, std::shared_ptr<Field> field) override;
};

} // engine

#endif //FINDPLACESTRATEGYSTD_H
