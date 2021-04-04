#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QDebug>

#include "tile.h"

class Rectangle final : public Tile
{
public:

    Rectangle() = default;
    ~Rectangle() = default;

    virtual Coordinates getNeighborCoords(Coordinates coords, const Direction &direction) override
    {
        switch (direction) {
            case Direction::North:
                coords.rowNum++;
                break;
            case Direction::East:
                coords.colNum++;
                break;
            case Direction::South:
                coords.rowNum--;
                break;
            case Direction::West:
                coords.colNum--;
                break;
            default:
                qFatal("invalid direction passed as function argument");
                break;
        }

        return coords;
    }

    virtual QVector<Direction> getDirections() override
    {
        return {Direction::North, Direction::East, Direction::South, Direction::West};
    }
};

#endif // RECTANGLE_H
