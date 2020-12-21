#ifndef HEXAGON_H
#define HEXAGON_H

#include "debug.h"
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
                coords.rowNum--;
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum : coords.colNum + 1;
                break;
            case Direction::East:
                coords.colNum++;
                break;
            case Direction::SouthEast:
                coords.rowNum++;
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum : coords.colNum + 1;
                break;
            case Direction::SouthWest:
                coords.rowNum++;
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum - 1 : coords.colNum;
                break;
            case Direction::West:
                coords.colNum--;
                break;
            case Direction::NorthWest:
                coords.rowNum--;
                coords.colNum = (coords.rowNum % 2 == 0) ? coords.colNum - 1 : coords.colNum;
                break;
            default:
                if(DEBUG_MSGS_ON) qDebug() << "[Hexagon] invalid direction passed as function argument" << Qt::endl;
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
