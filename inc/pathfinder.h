#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "searchgrid.h"
#include <list>

class PathFinder
{
public:
    PathFinder(SearchGrid &grid) : grid(grid) {};

    virtual bool initialize() = 0;
    virtual bool advance() = 0;
    virtual std::list<Field::Coordinates> getPath() = 0;

private:
    SearchGrid &grid;
};

#endif // PATHFINDER_H
