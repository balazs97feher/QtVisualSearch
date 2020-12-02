#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "searchgrid.h"
#include <list>

class PathFinder
{
public:
    using FieldCoords = Field::Coordinates;

    enum class Direction
    {
      Up, Right, Down, Left
    };
    static constexpr Direction directions[4] = {Direction::Up, Direction::Right, Direction::Down, Direction::Left};

    PathFinder(SearchGrid &grid) : grid(grid) {};

    virtual bool initialize() = 0;
    virtual bool advance() = 0;
    virtual std::list<Field::Coordinates> getPath() = 0;

protected:
    SearchGrid &grid;
    Field::Coordinates getNeighborCoords(FieldCoords field, const Direction &direction);
};

#endif // PATHFINDER_H

Field::Coordinates PathFinder::getNeighborCoords(FieldCoords field, const PathFinder::Direction &direction)
{
    switch (direction) {
        case PathFinder::Direction::Up:
            field.rowNum++;
        break;
        case PathFinder::Direction::Right:
            field.colNum++;
        break;
        case PathFinder::Direction::Down:
            field.rowNum--;
        break;
        case PathFinder::Direction::Left:
            field.colNum--;
        break;
    }

    return field;
}
