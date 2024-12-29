//
// Created by anton on 12/5/24.
//

#include "Field.h"

#include <memory>

using namespace gameEngine;

bool gameEngine::operator==(const Coord& posA, const Coord& posB)
{
    return posA.x == posB.x && posA.y == posB.y;
}

int Field::getWidth() const
{
    return width;
}

int Field::getHeight() const
{
    return height;
}

Field::Field(int iWidth, int iHeight) : width{iWidth}, height{iHeight}
{
}

Coord Field::canonizeCoord(const Coord& coord) const
{
    int cx = coord.x >= 0 ? coord.x % width : coord.x % width + width;
    int cy = coord.y >= 0 ? coord.y % height : coord.y % height + height;
    return {cx, cy};
}

void gameEngine::getNextPos(Coord &c, std::shared_ptr<Field> field)
{
    if (c.x == field->getWidth() - 1)
    {
        c.x = 0;
        ++c.y;
    } else
    {
        ++c.x;
    }
    c.y = c.y % field->getHeight();
}

