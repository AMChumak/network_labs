//
// Created by anton on 1/17/25.
//

#ifndef FIELD_H
#define FIELD_H
#include <memory>

namespace engine
{
    struct Coord
    {
        Coord(const int i_x = 0, const int i_y = 0): x{i_x}, y{i_y}
        {
        }

        int x;
        int y;
    };

    bool operator==(const Coord& pos_a, const Coord& pos_b);
    bool operator!=(const Coord& pos_a, const Coord& pos_b);
    Coord &operator+=(Coord& pos_a, const Coord& pos_b);
    Coord operator+(const Coord& pos_a, const Coord& pos_b);

    /*
     *Field has discrete toroidal form
     */
    class Field
    {
    public:
        int get_width() const;
        int get_height() const;

        Field(int width = 40, int height = 30);
        Coord canonize_coord(const Coord& coord) const;
        Coord &canonize_coord(Coord& coord) const;

    private:
        const int width;
        const int height;
    };

    Coord get_next_pos(const Coord& coord, const std::shared_ptr<Field>& field);
    Coord &get_next_pos(Coord& coord, const std::shared_ptr<Field>& field);
} // engine

#endif //FIELD_H
