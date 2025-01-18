//
// Created by anton on 12/5/24.
//

#include "EatStrategyStd.h"

namespace engine {
    void EatStrategyStd::eat(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> food_distr)
    {
        for (auto snake= snakes->begin(); snake != snakes->end(); ++snake)
        {
            for (auto food: food_distr->get_foods())
            {
                if (snake->intersect(food))
                {
                    snake->grow();
                    break;
                }
            }
        }

        for (auto it = food_distr->get_foods().begin(); it != food_distr->get_foods().end(); )
        {
            bool found = false;
            for (auto snake: *snakes)
            {
                if (snake.intersect(*it))
                {
                    found = true;
                    it = food_distr->erase_food(it);
                    break;
                }
            }

            if (!found)
                ++it;
        }
    }
} // engine