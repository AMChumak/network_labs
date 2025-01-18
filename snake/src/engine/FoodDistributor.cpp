//
// Created by anton on 12/5/24.
//

#include "FoodDistributor.h"


#include <random>

namespace engine
{
    FoodDistributor::FoodDistributor(std::shared_ptr<Field> i_field, std::shared_ptr<std::vector<Snake>> i_snakes,
                                     const int& min_limit_food) : min_foods_size{min_limit_food},
                                                                  field{std::move(i_field)},
                                                                  snakes{std::move(i_snakes)}
    {
    }

    /*!
     *
     * @return reference to const vector of food coordinates
     */
    const std::vector<Coord>& FoodDistributor::get_foods()
    {
        return foods;
    }


    bool check_empty(const std::shared_ptr<std::vector<Snake>>& snakes, const std::vector<Coord>& foods,
                     const Coord& pos)
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

    /*!
     * @brief refills food vector
     */
    void FoodDistributor::refill_food()
    {
        while (foods.size() < min_foods_size + snakes->size())
        {
            Coord pos = field->canonize_coord(Coord{rand(), rand()});

            if (check_empty(snakes, foods, pos))
            {
                foods.push_back(pos);
                continue;
            }

            Coord cur_pos = pos;
            get_next_pos(cur_pos, field);

            bool added_food = false;

            while (cur_pos != pos)
            {
                if (check_empty(snakes, foods, cur_pos))
                {
                    foods.push_back(pos);
                    added_food = true;
                    break;
                }
            }

            if (!added_food)
            {
                break;
            }
        }
    }

    /*!
     * @brief loads food by state
     * @param [in] state state of the game
     */
    void FoodDistributor::fill_food(const GameState& state)
    {
        foods.clear();
        for (int i = 0, end = state.foods_size(); i != end; ++i)
        {
            foods.emplace_back(state.foods(i).x(), state.foods(i).y());
        }
    }

    std::vector<Coord>::const_iterator FoodDistributor::erase_food(std::vector<Coord>::const_iterator iter)
    {
        return foods.erase(iter);
    }
} // gameEngine
