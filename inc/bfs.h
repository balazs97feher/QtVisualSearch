#ifndef BFS_H
#define BFS_H

#include "debug.h"

#include "pathfinder.h"

class BFS: public PathFinder
{
public:
    BFS(SearchGrid &grid);

    virtual bool initialize() override;
    virtual bool advance() override;
    virtual std::list<Field::Coordinates> getPath() override;
};

#endif // BFS_H
