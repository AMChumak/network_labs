//
// Created by anton on 12/5/24.
//

#ifndef FOODDISTRIBUTOR_H
#define FOODDISTRIBUTOR_H
#include <memory>
#include <vector>

#include "Snake.h"


namespace engine
{
    class FoodDistributor
    {
    public:
        FoodDistributor(std::shared_ptr<Field> i_field, std::shared_ptr<std::vector<Snake>> i_snakes,
                        const int& min_limit_food = 1);

        const std::vector<Coord>& get_foods();
        void refill_food();
        void fill_food(const GameState& state);
        std::vector<Coord>::const_iterator erase_food(std::vector<Coord>::const_iterator iter);

    private:
        int min_foods_size;
        std::vector<Coord> foods;
        std::shared_ptr<Field> field;
        std::shared_ptr<std::vector<Snake>> snakes;
    };
} // gameEngine

#endif //FOODDISTRIBUTOR_H
