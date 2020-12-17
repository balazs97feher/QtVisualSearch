#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "debug.h"
#include "tile.h"

class Rectangle final : public Tile
{
public:

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
                if(DEBUG_MSGS_ON) qDebug() << "[Rectangle] invalid direction passed as function argument" << Qt::endl;
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