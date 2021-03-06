#ifndef SEARCHGRID_H
#define SEARCHGRID_H

#include <QVector>
#include <memory>

#include "tile.h"

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
    const Tiling tiling;
    QVector<QVector<std::shared_ptr<Tile>>> tiles;
    uint rowCount, colCount;

    std::shared_ptr<Tile> startTile, destTile;
    TileCoords startCoords, destCoords;

    void resizeGrid();
};

#endif // SEARCHGRID_H
