#ifndef TILE_H
#define TILE_H

#include <QVector>

class Tile
{
public:

    enum class Type
    {
        Empty,
        Wall,
        Start,
        Destination,
        Visited,
        Path
    };
    Type type;

    enum class Direction
    {
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest
    };

    struct Coordinates
    {
        unsigned int rowNum, colNum;
    };

    Tile() : type(Type::Empty) {};
    ~Tile() = default;

    virtual Coordinates getNeighborCoords(Coordinates, const Direction&) = 0;
    virtual QVector<Direction> getDirections() = 0;
};

#endif // TILE_H
