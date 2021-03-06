#ifndef HEXAGON_H
#define HEXAGON_H

#include <QDebug>

#include "tile.h"

class Hexagon final : public Tile
{
public:

    Hexagon() = default;
    ~Hexagon() = default;

    virtual Coordinates getNeighborCoords(Coordinates coords, const Direction &direction) override
    {
        switch (direction) {
            case Direction::NorthEast:
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum : coords.colNum + 1;
                coords.rowNum--;
                break;
            case Direction::East:
                coords.colNum++;
                break;
            case Direction::SouthEast:
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum : coords.colNum + 1;
                coords.rowNum++;
                break;
            case Direction::SouthWest:
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum - 1 : coords.colNum;
                coords.rowNum++;
                break;
            case Direction::West:
                coords.colNum--;
                break;
            case Direction::NorthWest:
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum - 1 : coords.colNum;
                coords.rowNum--;
                break;
            default:
                qFatal("invalid direction passed as function argument");
                break;
        }

        return coords;
    }

    virtual QVector<Direction> getDirections() override
    {
        return {Direction::NorthEast, Direction::East, Direction::SouthEast, Direction::SouthWest, Direction::West, Direction::NorthWest};
    }
};

#endif // HEXAGON_H
