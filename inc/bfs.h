#ifndef BFS_H
#define BFS_H

#include "debug.h"

#include "pathfinder.h"
#include <list>
#include <QVector>

class BFS: public PathFinder
{
public:
    using FieldCoords = Field::Coordinates;
    using FieldType = Field::Type;

    BFS(SearchGrid &grid);

    virtual bool initialize() override;
    virtual bool advance() override;
    virtual std::list<FieldCoords> getPath() override;

private:

    FieldCoords currentField;
    uint dirIndex;
    std::list<FieldCoords> fieldsToCheck;
    QVector<QVector<FieldCoords>> previousField;
};

#endif // BFS_H
