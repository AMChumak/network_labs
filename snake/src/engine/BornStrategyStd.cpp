//
// Created by anton on 12/6/24.
//

#include "BornStrategyStd.h"
#include "Snake.h"
namespace engine {
    bool BornStrategyStd::born(const int &owner_id, std::shared_ptr<std::vector<Snake>> snakes, const std::shared_ptr<FoodDistributor> food_distr,
        std::shared_ptr<Field> field, const std::shared_ptr<FindPlaceStrategyI> find_place_strategy)
    {
        CoordDirectionPair pos = find_place_strategy->find_place(snakes, food_distr, field);

        if (pos.coord == incorrect_pair.coord )
        {
            return false;
        }
        snakes->emplace_back(owner_id, pos.coord, pos.direction, field);
        return true;
    }
} // engine