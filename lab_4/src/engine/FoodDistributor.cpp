//
// Created by anton on 12/5/24.
//

#include "FoodDistributor.h"


#include <random>
#include <bits/struct_stat.h>

namespace gameEngine {
    FoodDistributor::FoodDistributor(std::shared_ptr<Field> iField, std::shared_ptr<std::vector<Snake>> iSnakes, const int &minLimitFood) : field{std::move(iField)}, snakes{std::move(iSnakes)}, minFoodsSize{minLimitFood}
    {
    }

    FoodDistributor::FoodDistributor(std::shared_ptr<Field> iField, std::shared_ptr<std::vector<Snake>> iSnakes,
        const GameState& state) : field{std::move(iField)}, snakes{std::move(iSnakes)}
    {
        minFoodsSize = state.foods_size() - state.snakes_size();
        for (int i = 0,end = state.foods_size(); i != end; ++i)
        {
            foods.emplace_back(state.foods(i).x(), state.foods(i).y());
        }
    }

    const std::vector<Coord>& FoodDistributor::getFoods()
    {
        return foods;
    }

    bool checkEmpty(const std::shared_ptr<std::vector<Snake>>& snakes, const std::vector<Coord> &foods, const Coord &pos)
    {
        for (auto food : foods)
        {
            if (food == pos)
            {
                return false;
            }
        }

        for (auto snake : *snakes)
        {
            if (snake.intersect(pos)) return false;
        }
        return true;
    }

    void FoodDistributor::fillFood()
    {
        while (foods.size() < minFoodsSize + snakes->size())
        {
            Coord pos = {rand() % field->getWidth(), rand() % field->getHeight()};

            if (checkEmpty(snakes, foods, pos))
            {
                foods.push_back(pos);
                continue;
            }

            Coord curPos = pos;
            getNextPos(curPos, field);

            bool addedFood = false;

            while (!(curPos == pos))
            {
                if (checkEmpty(snakes, foods, curPos))
                {
                    foods.push_back(pos);
                    addedFood = true;
                    break;
                }
            }

            if (!addedFood)
            {
                break;
            }
        }
    }

    std::vector<Coord>::const_iterator FoodDistributor::eraseFood(std::vector<Coord>::const_iterator it)
    {
        return foods.erase(it);
    }
} // gameEngine