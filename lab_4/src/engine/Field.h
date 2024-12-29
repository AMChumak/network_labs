//
// Created by anton on 12/5/24.
//

#ifndef FIELD_H
#define FIELD_H
#include <memory>


namespace gameEngine
{
    struct Coord
    {
        Coord(int ix, int iy): x{ix}, y{iy} {}

        int x;
        int y;
    };

    bool operator==(const Coord& posA, const Coord& posB);


    class Field {
    public:
        int getWidth() const;
        int getHeight() const;

        Field(int width = 40, int height = 30);
        Coord canonizeCoord(const Coord &coord) const;

    private:
        const int width;
        const int height;
    };

    void getNextPos(Coord &c, std::shared_ptr<Field> field);
}



#endif //FIELD_H
