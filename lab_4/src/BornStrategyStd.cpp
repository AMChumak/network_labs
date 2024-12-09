//
// Created by anton on 12/6/24.
//

#include "BornStrategyStd.h"

namespace gameEngine {
    bool BornStrategyStd::born(const int &ownerId, std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> foodDistr,
        std::shared_ptr<Field> field, std::shared_ptr<FindPlaceStrategyI> findPlaceStrategy)
    {
        CoordDirectionPair pos = findPlaceStrategy->findPlace(snakes, foodDistr, field);

        if (pos.coord == Coord{-1, -1} )
        {
            return false;
        }
        snakes->emplace_back(ownerId, pos.coord, pos.direction, field);
        return true;
    }
} // gameEngineв