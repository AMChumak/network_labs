//
// Created by anton on 12/6/24.
//

#include "FindPlaceStrategyStd.h"

#include <random>


namespace gameEngine
{
    bool checkNoFood(const std::vector<Coord> &foods, const Coord& pos)
    {
        for (auto food : foods)
        {
            if (food == pos)
                return false;
        }
        return true;
    }

    bool checkNoSnake(std::shared_ptr<std::vector<Snake>> snakes, const Coord& pos)
    {
        for (auto snake : *snakes)
        {
            if (snake.intersect(pos))
                return false;
        }
        return true;
    }

    bool checkSquare (const Coord &topLeftCorner, int side, std::shared_ptr<std::vector<Snake>> snakes,
                                         std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field, Direction *direction)
    {
        for (int x = 0; x < side; ++x)
        {
            for (int y = 0; y < side; ++y)
            {
                if (!checkNoSnake(snakes, field->canonizeCoord({topLeftCorner.x + x, topLeftCorner.y + y})))
                    return false;
            }
        }
        if (!checkNoFood(foodDistr->getFoods(), field->canonizeCoord({topLeftCorner.x + 2, topLeftCorner.y + 2})))
            return false;

        if (checkNoFood(foodDistr->getFoods(), field->canonizeCoord({topLeftCorner.x + 2, topLeftCorner.y + 1})))
        {
            *direction = DOWN;
            return true;
        }

        if (checkNoFood(foodDistr->getFoods(), field->canonizeCoord({topLeftCorner.x + 2, topLeftCorner.y + 3})))
        {
            *direction = UP;
            return true;
        }

        if (checkNoFood(foodDistr->getFoods(), field->canonizeCoord({topLeftCorner.x + 1, topLeftCorner.y + 2})))
        {
            *direction = RIGHT;
            return true;
        }

        if (checkNoFood(foodDistr->getFoods(), field->canonizeCoord({topLeftCorner.x + 3, topLeftCorner.y + 2})))
        {
            *direction = LEFT;
            return true;
        }

        return false;
    }


    CoordDirectionPair FindPlaceStrategyStd::findPlace(std::shared_ptr<std::vector<Snake>> snakes,
                                         std::shared_ptr<FoodDistributor> foodDistr, std::shared_ptr<Field> field)
    {
        int squareSide = 5;

        Coord pos = {rand() % field->getWidth(), rand() % field->getHeight()};
        Direction resD = UP;
        if (checkSquare(pos, squareSide, snakes, foodDistr, field, &resD))
        {
            return {pos,resD};
        }

        Coord curPos = pos;
        getNextPos(curPos, field);

        while (!(curPos == pos))
        {
            if (checkSquare(pos, squareSide, snakes, foodDistr, field, &resD))
            {
                return {curPos, resD};
            }
        }
        return {{-1, -1},resD};
    }
} // gameEngine
