//
// Created by anton on 1/17/25.
//

#include "Field.h"

#include <memory>

using namespace engine;

bool engine::operator==(const Coord& pos_a, const Coord& pos_b)
{
    return pos_a.x == pos_b.x && pos_a.y == pos_b.y;
}

bool engine::operator!=(const Coord& pos_a, const Coord& pos_b)
{
    return !(pos_a == pos_b);
}

Coord& engine::operator+=(Coord& pos_a, const Coord& pos_b)
{
    pos_a.x += pos_b.x;
    pos_a.y += pos_b.y;
    return pos_a;
}

Coord engine::operator+(const Coord& pos_a, const Coord& pos_b)
{
    Coord pos_a1(pos_a);
    pos_a1 += pos_b;
    return pos_a1;
}

int Field::get_width() const
{
    return width;
}

int Field::get_height() const
{
    return height;
}

Field::Field(const int width, const int height) : width{width}, height{height}
{
}

/*!
 * @brief Canonizes coordinate for fields parameters
 * @param [in] coord coordinates
 * @return coordinates modulo the size of the field
 */
Coord Field::canonize_coord(const Coord& coord) const
{
    int coord_x = coord.x >= 0 ? coord.x % width : coord.x % width + width;
    int coord_y = coord.y >= 0 ? coord.y % height : coord.y % height + height;
    return {coord_x, coord_y};
}

Coord& Field::canonize_coord(Coord& coord) const
{
    coord.x = coord.x >= 0 ? coord.x % width : coord.x % width + width;
    coord.y = coord.y >= 0 ? coord.y % height : coord.y % height + height;
    return coord;
}


/*!
 * @brief gets coordinates of the next cell in format:
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * @param [in] coord current coordinates
 * @param [in] field the field that is being crawled
 * @return next coordinates in bypass
 */
Coord engine::get_next_pos(const Coord& coord, const std::shared_ptr<Field>& field)
{
    Coord next_pos = coord;
    if (coord.x == field->get_width() - 1)
    {
        next_pos.x = 0;
        next_pos.y = coord.y + 1;
    } else
    {
        next_pos.x = coord.x + 1;
    }
    next_pos.y = coord.y % field->get_height();
    return next_pos;
}

/*!
 * @brief gets coordinates of the next cell in format:
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * @param [in] coord current coordinates
 * @param [in] field the field that is being crawled
 * @return next coordinates in bypass
 */
Coord &engine::get_next_pos(Coord &coord, const std::shared_ptr<Field>& field)
{
    if (coord.x == field->get_width() - 1)
    {
        coord.x = 0;
        ++coord.y;
    } else
    {
        ++coord.x;
    }
    coord.y = coord.y % field->get_height();
    return coord;
}
