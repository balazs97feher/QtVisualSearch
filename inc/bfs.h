#ifndef BFS_H
#define BFS_H

#include "debug.h"

#include "pathfinder.h"
#include <list>
#include <QVector>

class BFS: public PathFinder
{
public:
    BFS(SearchGrid &grid);

    virtual bool initialize() override;
    virtual bool advance() override;
    virtual std::list<Field::Coordinates> getPath() override;

private:
    using FieldCoords = Field::Coordinates;

    FieldCoords currentField;
    uint dirIndex;
    std::list<FieldCoords> fieldsToCheck;
    QVector<QVector<Field*>> previousField;
};

#endif // BFS_H
