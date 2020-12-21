#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "searchgrid.h"
#include <list>

class PathFinder
{
public:
    using TileCoords = Tile::Coordinates;

    PathFinder(std::shared_ptr<SearchGrid> grid) : grid(grid) {};

    virtual bool initialize() = 0;
    virtual bool advance() = 0;
    virtual std::list<TileCoords> getPath() = 0;

protected:
    std::shared_ptr<SearchGrid> grid;
    QVector<Tile::Direction> directions;
    uint directionCount;
};

#endif // PATHFINDER_H
