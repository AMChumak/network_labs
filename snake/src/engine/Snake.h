#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>

#include "Field.h"
#include "../proto/snakes.pb.h"


namespace engine
{
    struct CoordDirectionPair
    {
        Coord coord;
        Direction direction;
    };

    inline CoordDirectionPair incorrect_pair = {{-1,-1}, UP};

    class Snake
    {
    public:
        Snake(const int& i_owner_id, const Coord& i_head_coord, const Direction& i_head_direction, std::shared_ptr<Field> field_ptr);

        Snake(const GameState_Snake &i_snake, const std::shared_ptr<Field>& field_ptr);

        GameState_Snake generate_state();

        void step();
        void grow();
        void turn(Direction direction);

        int get_owner_id() const;
        std::vector<Coord> get_body() const;
        bool intersect(const Coord& check_coord) const;
        Coord get_head_coord() const;
        Direction get_head_direction() const;
        std::shared_ptr<Field> get_field() const;


    private:
        std::shared_ptr<Field> field;
        int owner_id;
        Direction head_direction;
        Direction tail_direction;
        std::vector<Coord> key_coords; //first is coordinate of the head, other coordinates - sequence of offsets
    };


} // gameEngine

#endif //SNAKE_H
