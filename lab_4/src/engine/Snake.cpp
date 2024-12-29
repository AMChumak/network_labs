//
// Created by anton on 12/5/24.
//

#include "Snake.h"

#include <iostream>
#include <set>
#include <utility>

namespace gameEngine
{
    Snake::Snake(const int& iOwnerId, const Coord& iHeadCoord, const Direction& iHeadDirection,
                 std::shared_ptr<Field> fieldPtr) : ownerId(iOwnerId), headDirection(iHeadDirection),
                                                    field{std::move(fieldPtr)}
    {
        keyCoords.push_back(field->canonizeCoord(iHeadCoord));
        switch (iHeadDirection)
        {
        case UP:
            {
                tailDirection = DOWN;
                keyCoords.push_back({0, 1});
                break;
            }
        case DOWN:
            {
                tailDirection = UP;
                keyCoords.push_back({0, -1});
                break;
            }
        case LEFT:
            {
                tailDirection = RIGHT;
                keyCoords.push_back({1, 0});
                break;
            }
        case RIGHT:
            {
                tailDirection = LEFT;
                keyCoords.push_back({-1, 0});
                break;
            }
        }
    }

    Snake::Snake(const GameState_Snake& iSnake): ownerId{iSnake.player_id()}
    {
        switch (iSnake.head_direction())
        {
        case ::UP:
            {
                headDirection = UP;
                break;
            }
        case ::DOWN:
            {
                headDirection = DOWN;
                break;
            }
        case ::LEFT:
            {
                headDirection = LEFT;
                break;
            }
        case ::RIGHT:
            {
                headDirection = RIGHT;
                break;
            }
        }

        for (const auto& point : iSnake.points())
        {
            keyCoords.emplace_back(point.x(), point.y());
        }

        if (keyCoords.back().x)
        {
            if (keyCoords.back().x > 0)
            {
                tailDirection = RIGHT;
            }
            else
            {
                tailDirection = LEFT;
            }
        }
        else
        {
            if (keyCoords.back().y > 0)
            {
                tailDirection = DOWN;
            }
            else
            {
                tailDirection = UP;
            }
        }
    }


    void Snake::step()
    {
        //MOVE HEAD

        int stepX = 0, stepY = 0;

        switch (headDirection)
        {
        case UP:
            {
                stepY = -1;
                break;
            }
        case DOWN:
            {
                stepY = 1;
                break;
            }
        case LEFT:
            {
                stepX = -1;
                break;
            }
        case RIGHT:
            {
                stepX = 1;
                break;
            }
        }

        // if direction changed, then create new key coordinate
        if ((keyCoords[1].x == 0 && stepX == 0) || (keyCoords[1].y == 0 && stepY == 0))
        {
            keyCoords[0] = field->canonizeCoord({keyCoords[0].x + stepX, keyCoords[0].y + stepY}); //change head coords
            keyCoords[1] = {keyCoords[1].x - stepX, keyCoords[1].y - stepY}; // change offset of neck
        }
        else
        {
            // insert new keyCoord
            keyCoords.insert(keyCoords.begin(), field->canonizeCoord({keyCoords[0].x + stepX, keyCoords[0].y + stepY}));
            keyCoords[1] = {-stepX, -stepY}; //change offset of new neck
        }

        //MOVE TAIL
        //we should remember last direction of tail because
        //snake could will grow after step, then tail will be the corner

        Coord& tail = *(keyCoords.end() - 1);
        if (tail.y < 0)
        {
            tailDirection = UP;
            if (tail.y == -1) keyCoords.pop_back();
            else ++tail.y;
        }
        else if (tail.y > 0)
        {
            tailDirection = DOWN;
            if (tail.y == 1) keyCoords.pop_back();
            else --tail.y;
        }
        else if (tail.x < 0)
        {
            tailDirection = LEFT;
            if (tail.x == -1) keyCoords.pop_back();
            else ++tail.x;
        }
        else
        {
            tailDirection = RIGHT;
            if (tail.x == 1) keyCoords.pop_back();
            else --tail.x;
        }
    }


    void Snake::grow()
    {
        Coord& tail = *(keyCoords.end() - 1);
        int stepX = 0, stepY = 0;

        switch (tailDirection)
        {
        case UP:
            {
                stepY = -1;
                break;
            }
        case DOWN:
            {
                stepY = 1;
                break;
            }
        case LEFT:
            {
                stepX = -1;
                break;
            }
        case RIGHT:
            {
                stepX = 1;
                break;
            }
        }

        // if corner case, then create new key coordinate
        if ((tail.x == 0 && stepX == 0) || (tail.y == 0 && stepY == 0))
        {
            tail.x = tail.x + stepX;
            tail.y = tail.y + stepY; //change tail offset
        }
        else
        {
            // insert new keyCoord
            keyCoords.emplace_back(stepX, stepY);
        }
    }


    void Snake::turn(Direction direction)
    {
        const Coord& neck = keyCoords[1];
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
        headDirection = direction;
    }


    int Snake::getOwnerId() const
    {
        return ownerId;
    }

    std::shared_ptr<std::vector<Coord>> Snake::getBody()
    {
        auto body = std::make_shared<std::vector<Coord>>();

        body->push_back(keyCoords[0]);
        Coord lastCoord = field->canonizeCoord(keyCoords[0]);
        for (int i = 1, limit = keyCoords.size(); i < limit; ++i)
        {
            Coord offset = keyCoords[i];
            int mx = 0, my = 0;

            if (offset.x < 0) mx = -1;
            else if (offset.x > 0) mx = 1;
            else if (offset.y < 0) my = -1;
            else if (offset.y > 0) my = 1;

            Coord next = field->canonizeCoord({lastCoord.x + offset.x, lastCoord.y + offset.y});
            while (next.x != lastCoord.x || next.y != lastCoord.y)
            {
                lastCoord.x += mx;
                lastCoord.y += my;
                lastCoord = field->canonizeCoord(lastCoord);
                body->push_back(lastCoord);
            }
        }

        return body;
    }

    bool Snake::intersect(const Coord& checkCoord)
    {
        Coord canonizedCheck = field->canonizeCoord(checkCoord);
        Coord lastCoord = keyCoords[0];
        if (lastCoord == canonizedCheck)
        {
            return true;
        }
        for (int i = 1, limit = keyCoords.size(); i < limit; ++i)
        {
            Coord offset = keyCoords[i];
            int mx = 0, my = 0;

            if (offset.x < 0) mx = -1;
            else if (offset.x > 0) mx = 1;
            else if (offset.y < 0) my = -1;
            else if (offset.y > 0) my = 1;

            Coord next = field->canonizeCoord({lastCoord.x + offset.x, lastCoord.y + offset.y});
            while (next.x != lastCoord.x || next.y != lastCoord.y)
            {
                lastCoord.x += mx;
                lastCoord.y += my;
                lastCoord = field->canonizeCoord(lastCoord);
                if (lastCoord == canonizedCheck)
                {
                    return true;
                }
            }
        }
        return false;
    }

    Coord Snake::getHeadCoord()
    {
        return keyCoords[0];
    }

    Direction Snake::getHeadDirection()
    {
        return headDirection;
    }

    std::shared_ptr<Field> Snake::getField()
    {
        return field;
    }
} // gameEngine
