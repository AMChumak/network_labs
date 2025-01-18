//
// Created by anton on 12/5/24.
//

#include "Snake.h"


#include <utility>

namespace engine
{
    Snake::Snake(const int& i_owner_id, const Coord& i_head_coord, const Direction& i_head_direction,
                 std::shared_ptr<Field> field_ptr) : field{std::move(field_ptr)}, owner_id(i_owner_id), head_direction(i_head_direction)

    {
        key_coords.push_back(field->canonize_coord(i_head_coord));
        switch (i_head_direction)
        {
        case UP:
            {
                tail_direction = DOWN;
                key_coords.push_back({0, 1});
                break;
            }
        case DOWN:
            {
                tail_direction = UP;
                key_coords.push_back({0, -1});
                break;
            }
        case LEFT:
            {
                tail_direction = RIGHT;
                key_coords.push_back({1, 0});
                break;
            }
        case RIGHT:
            {
                tail_direction = LEFT;
                key_coords.push_back({-1, 0});
                break;
            }
        }
    }

    Snake::Snake(const GameState_Snake& i_snake, const std::shared_ptr<Field>& field_ptr): field{field_ptr},
        owner_id{i_snake.player_id()}
    {
        switch (i_snake.head_direction())
        {
        case ::UP:
            {
                head_direction = UP;
                break;
            }
        case ::DOWN:
            {
                head_direction = DOWN;
                break;
            }
        case ::LEFT:
            {
                head_direction = LEFT;
                break;
            }
        case ::RIGHT:
            {
                head_direction = RIGHT;
                break;
            }
        }

        for (const auto& point : i_snake.points())
        {
            key_coords.emplace_back(point.x(), point.y());
        }

        if (key_coords.back().x)
        {
            if (key_coords.back().x > 0)
            {
                tail_direction = RIGHT;
            }
            else
            {
                tail_direction = LEFT;
            }
        }
        else
        {
            if (key_coords.back().y > 0)
            {
                tail_direction = DOWN;
            }
            else
            {
                tail_direction = UP;
            }
        }
    }

    /*!
     * \brief moves the snake forward 1 cell in the direction of the head
     */
    void Snake::step()
    {
        //MOVE HEAD
        int step_x = 0, step_y = 0;

        switch (head_direction)
        {
        case UP:
            {
                step_y = -1;
                break;
            }
        case DOWN:
            {
                step_y = 1;
                break;
            }
        case LEFT:
            {
                step_x = -1;
                break;
            }
        case RIGHT:
            {
                step_x = 1;
                break;
            }
        }

        // if direction changed, then create new key coordinate
        if ((key_coords[1].x == 0 && step_x == 0) || (key_coords[1].y == 0 && step_y == 0))
        {
            key_coords[0] = field->canonize_coord({key_coords[0].x + step_x, key_coords[0].y + step_y});
            //change head coords
            key_coords[1] = {key_coords[1].x - step_x, key_coords[1].y - step_y}; // change offset of neck
        }
        else
        {
            // insert new keyCoord
            key_coords.insert(key_coords.begin(),
                              field->canonize_coord({key_coords[0].x + step_x, key_coords[0].y + step_y}));
            key_coords[1] = {-step_x, -step_y}; //change offset of new neck
        }

        //MOVE TAIL
        //we should remember last direction of tail because
        //if snake grows after step, then current tail can become an angle

        Coord& tail = *(key_coords.end() - 1);
        if (tail.y < 0)
        {
            tail_direction = UP;
            if (tail.y == -1) key_coords.pop_back();
            else ++tail.y;
        }
        else if (tail.y > 0)
        {
            tail_direction = DOWN;
            if (tail.y == 1) key_coords.pop_back();
            else --tail.y;
        }
        else if (tail.x < 0)
        {
            tail_direction = LEFT;
            if (tail.x == -1) key_coords.pop_back();
            else ++tail.x;
        }
        else
        {
            tail_direction = RIGHT;
            if (tail.x == 1) key_coords.pop_back();
            else --tail.x;
        }
    }

    /*!
     * \brief  increases snake's length by 1 cell in the direction of the tail
     */
    void Snake::grow()
    {
        Coord& tail = *(key_coords.end() - 1);
        int step_x = 0, step_y = 0;

        switch (tail_direction)
        {
        case UP:
            {
                step_y = -1;
                break;
            }
        case DOWN:
            {
                step_y = 1;
                break;
            }
        case LEFT:
            {
                step_x = -1;
                break;
            }
        case RIGHT:
            {
                step_x = 1;
                break;
            }
        }

        // if corner case, then create new key coordinate
        if ((tail.x == 0 && step_x == 0) || (tail.y == 0 && step_y == 0))
        {
            tail.x = tail.x + step_x;
            tail.y = tail.y + step_y; //change tail offset
        }
        else
        {
            // insert new keyCoord
            key_coords.emplace_back(step_x, step_y);
        }
    }

    /*!
     * \brief changes direction of the snake. Snake can't turn the head back
     * @param direction new direction of the head
     */
    void Snake::turn(Direction direction)
    {
        const Coord& neck = key_coords[1];
        switch (direction)
        {
        case UP:
            {
                if (neck.x == 0 && neck.y < 0) return;
                break;
            }
        case DOWN:
            {
                if (neck.x == 0 && neck.y > 0) return;
                break;
            }
        case LEFT:
            {
                if (neck.x < 0 && neck.y == 0) return;
                break;
            }
        case RIGHT:
            {
                if (neck.x > 0 && neck.y == 0) return;
                break;
            }
        }
        head_direction = direction;
    }


    int Snake::get_owner_id() const
    {
        return owner_id;
    }

    /*!
     * @return a sequence of canonized coordinates of the snake in order from head to tail
     */
    std::vector<Coord> Snake::get_body() const
    {
        auto body = std::vector<Coord>();

        body.push_back(key_coords[0]);
        Coord last_coord = field->canonize_coord(key_coords[0]);
        for (int i = 1, limit = key_coords.size(); i < limit; ++i)
        {
            Coord offset = key_coords[i];
            Coord offset_direction = {
                offset.x ? offset.x / abs(offset.x) : offset.x,
                offset.y ? offset.y / abs(offset.y) : offset.y
            };

            Coord next = field->canonize_coord(last_coord + offset);
            while (next != last_coord)
            {
                last_coord += offset_direction;
                body.push_back(field->canonize_coord(last_coord));
            }
        }

        return body;
    }

    /*!
     * @brief checks if the snake intersects coordinate
     * @param [in] check_coord examined coordinate
     * @return true if intersects, false - else
     */
    bool Snake::intersect(const Coord& check_coord) const
    {
        Coord canonized_check = field->canonize_coord(check_coord);
        Coord last_coord = key_coords[0];
        if (last_coord == canonized_check)
        {
            return true;
        }
        for (int i = 1, limit = key_coords.size(); i < limit; ++i)
        {
            Coord offset = key_coords[i];
            Coord offset_direction = {
                offset.x ? offset.x / abs(offset.x) : offset.x,
                offset.y ? offset.y / abs(offset.y) : offset.y
            };

            Coord next = field->canonize_coord(last_coord + offset);
            while (next != last_coord)
            {
                last_coord += offset_direction;
                if (check_coord == field->canonize_coord(last_coord))
                {
                    return true;
                }
            }
        }
        return false;
    }

    Coord Snake::get_head_coord() const
    {
        return key_coords[0];
    }

    Direction Snake::get_head_direction() const
    {
        return head_direction;
    }

    std::shared_ptr<Field> Snake::get_field() const
    {
        return field;
    }
} // gameEngine
