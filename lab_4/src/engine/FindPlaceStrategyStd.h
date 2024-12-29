//
// Created by anton on 12/6/24.
//

#ifndef FINDPLACESTRATEGYSTD_H
#define FINDPLACESTRATEGYSTD_H
#include "MoveStrategies.h"

namespace gameEngine {

class FindPlaceStrategyStd : public FindPlaceStrategyI{
public:
    //returns pair with coord: -1 ,-1 if not found
    CoordDirectionPair findPlace(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field) override;
};

} // gameEngine

#endif //FINDPLACESTRATEGYSTD_H
