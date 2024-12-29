//
// Created by anton on 12/5/24.
//

#include "EatStrategyStd.h"

namespace gameEngine {
    void EatStrategyStd::eat(std::shared_ptr<std::vector<Snake>> snakes, std::shared_ptr<FoodDistributor> foodDistr)
    {
        for (auto snake: *snakes)
        {
            for (auto food: foodDistr->getFoods())
            {
                if (snake.intersect(food))
                {
                    snake.grow();
                    break;
                }
            }
        }

        for (auto it = foodDistr->getFoods().begin(); it != foodDistr->getFoods().end(); )
        {
            for (auto snake: *snakes)
            {
                if (snake.intersect(*it))
                {
                    it = foodDistr->eraseFood(it);
                    break;
                }
            }
            ++it;
        }
    }
} // gameEngine