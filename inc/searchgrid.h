#ifndef SEARCHGRID_H
#define SEARCHGRID_H

#include "tile.h"
#include <QVector>
#include <memory>

class Canvas;
class BFS;

class SearchGrid
{
    friend class Canvas;
    friend class BFS;
    using TileType = Tile::Type;
    using TileCoords = Tile::Coordinates;

public:
    enum class Tiling
    {
        Rectangle,
        Hexagon
    };

    SearchGrid(const uint rowCount, const uint colCount, const Tiling shape);
    void setRowAndColCount(const uint rowCount, const uint colCount);
    void setStart(const TileCoords &coord);
    void clearStart();
    void setDest(const TileCoords &coord);
    void clearDest();
    std::shared_ptr<Tile> at(const TileCoords &coord);
    void resetMap();

private:
    const Tiling shape;
    QVector<QVector<std::shared_ptr<Tile>>> tiles;
    uint rowCount, colCount;

    std::shared_ptr<Tile> startTile, destTile;
    TileCoords startCoords, destCoords;
};

#endif // SEARCHGRID_H
