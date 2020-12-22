#ifndef BFS_H
#define BFS_H

#include "debug.h"

#include <QVector>
#include <list>

#include "pathfinder.h"

class BFS final : public PathFinder
{
public:
    using TileCoords = Tile::Coordinates;
    using TileType = Tile::Type;

    BFS(std::shared_ptr<SearchGrid> grid);

    virtual bool initialize() override;
    virtual bool advance() override;
    virtual std::list<TileCoords> getPath() override;

private:

    TileCoords currentTile;
    uint dirIndex;
    std::list<TileCoords> tilesToCheck;
    QVector<QVector<TileCoords>> previousTile;
};

#endif // BFS_H
