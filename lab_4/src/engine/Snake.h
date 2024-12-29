//
// Created by anton on 12/5/24.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <set>

#include "Field.h"
#include "snakes.pb.h"


namespace gameEngine
{
    enum Direction
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
    };

    struct CoordDirectionPair
    {
        Coord coord;
        Direction direction;
    };

    class Snake
    {
    public:
        Snake(const int& iOwnerId, const Coord& iHeadCoord, const Direction& iHeadDirection, std::shared_ptr<Field> fieldPtr);

        Snake(const GameState_Snake &iSnake);

        void step();
        void grow();
        void turn(Direction direction);

        int getOwnerId() const;
        std::shared_ptr<std::vector<Coord>> getBody();
        bool intersect(const Coord& checkCoord);
        Coord getHeadCoord();
        Direction getHeadDirection();
        std::shared_ptr<Field> getField();


    private:
        std::shared_ptr<Field> field;
        int ownerId;
        Direction headDirection;
        Direction tailDirection;
        std::vector<Coord> keyCoords;
    };


} // gameEngine

#endif //SNAKE_H
