//
// Created by anton on 12/6/24.
//

#include "FindPlaceStrategyStd.h"

#include <random>


namespace engine
{
    /*!
     * @brief checks that there is no food on position
     * @param [in] foods vector of foods in field
     * @param [in] pos examined position
     * @return true cell with chosen coordinates has no food, false - else
     */
    bool check_no_food(const std::vector<Coord> &foods, const Coord& pos)
    {
        for (auto food : foods)
        {
            if (food == pos)
                return false;
        }
        return true;
    }

    /*!
     * @brief checks that there is no snakes on position
     * @param [in] snakes shared pointer to vector of snakes in field
     * @param [in] pos examined position
     * @return true cell with chosen coordinates has no snakes, false - else
     */
    bool check_no_snake(const std::shared_ptr<std::vector<Snake>>& snakes, const Coord& pos)
    {
        for (auto snake : *snakes)
        {
            if (snake.intersect(pos))
                return false;
        }
        return true;
    }

    /*!
     * @brief checks that square has no snakes and exists cell next to center cell which has no food
     * @param [in] center top left corner of square
     * @param [in] side size of square's side. Must be odd number.
     * @param [in] snakes shared pointer to vector of snakes in field
     * @param [in] food_distr shared pointer to food distributor
     * @param [in] field shared pointer to field
     * @param [out] direction pointer to available head direction for new snake
     * @return true if place has been found, false - else
     */
    bool check_square (const Coord &center, const int side, std::shared_ptr<std::vector<Snake>> snakes,
                       std::shared_ptr<FoodDistributor> food_distr, std::shared_ptr<Field> field, Direction *direction)
    {

        for (int cur_x = -side/2; cur_x < side/2+1; ++cur_x)
        {
            for (int cur_y = -side/2; cur_y < side/2+1; ++cur_y)
            {
                if (!check_no_snake(snakes, field->canonize_coord({center.x + cur_x, center.y + cur_y})))
                    return false;
            }
        }
        if (!check_no_food(food_distr->get_foods(), field->canonize_coord({center.x, center.y})))
            return false;

        if (check_no_food(food_distr->get_foods(), field->canonize_coord({center.x, center.y -1})))
        {
            *direction = DOWN;
            return true;
        }

        if (check_no_food(food_distr->get_foods(), field->canonize_coord({center.x, center.y + 1})))
        {
            *direction = UP;
            return true;
        }

        if (check_no_food(food_distr->get_foods(), field->canonize_coord({center.x - 1, center.y})))
        {
            *direction = RIGHT;
            return true;
        }

        if (check_no_food(food_distr->get_foods(), field->canonize_coord({center.x + 1, center.y})))
        {
            *direction = LEFT;
            return true;
        }

        return false;
    }

    /*!
     * @brief finds place for new snake
     * @param [in] snakes shared pointer to vector of snakes in field
     * @param [in] food_distr shared pointer to food distributor
     * @param [in] field shared pointer to field
     * @return pair of head's coordinate and direction if place is found, incorrect_pair (see Snake.h)
     */
    CoordDirectionPair FindPlaceStrategyStd::find_place(const std::shared_ptr<std::vector<Snake>> snakes,
                                                        const std::shared_ptr<FoodDistributor> food_distr, std::shared_ptr<Field> field)
    {
        const int square_side = 5;

        const Coord pos = {rand() % field->get_width(), rand() % field->get_height()};
        Direction res_d = UP;
        if (check_square(pos, square_side, snakes, food_distr, field, &res_d))
        {
            return {pos,res_d};
        }

        Coord cur_pos = pos;
        get_next_pos(cur_pos, field);

        while (cur_pos != pos)
        {
            if (check_square(cur_pos, square_side, snakes, food_distr, field, &res_d))
            {
                return {cur_pos, res_d};
            }
            cur_pos = get_next_pos(cur_pos, field);
        }
        return incorrect_pair;
    }
} // engine
