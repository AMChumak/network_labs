//
// Created by anton on 12/5/24.
//

#ifndef FOODDISTRIBUTOR_H
#define FOODDISTRIBUTOR_H
#include <memory>
#include <vector>

#include "Snake.h"

namespace gameEngine {

class FoodDistributor {
public:
    FoodDistributor(std::shared_ptr<Field> iField, std::shared_ptr<std::vector<Snake>> iSnakes, const int &minLimitFood = 1);

    FoodDistributor(std::shared_ptr<Field> iField, std::shared_ptr<std::vector<Snake>> iSnakes, const GameState& state);

    const std::vector<Coord> &getFoods();
    void fillFood();
    std::vector<Coord>::const_iterator eraseFood(std::vector<Coord>::const_iterator it);

private:
    int minFoodsSize;
    std::vector<Coord> foods;
    std::shared_ptr<Field> field;
    std::shared_ptr<std::vector<Snake>> snakes;
};


} // gameEngine

#endif //FOODDISTRIBUTOR_H
