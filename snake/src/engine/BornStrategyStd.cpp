//
// Created by anton on 12/6/24.
//

#include "BornStrategyStd.h"
#include "Snake.h"
namespace engine {
    /*!
     * @brief adds new snake to field
     * @param owner_id id of snake's owner
     * @param snakes shared pointer to snakes in field
     * @param food_distr shared pointer to food distributor
     * @param field shared pointer to field
     * @param find_place_strategy shared pointer to find place strategy
     * @return true in success case, false - else
     */
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