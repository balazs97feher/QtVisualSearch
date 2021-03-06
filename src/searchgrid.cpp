#include "searchgrid.h"
#include "rectangle.h"
#include "hexagon.h"

SearchGrid::SearchGrid(const uint rowCount, const uint colCount, const Tiling shape) :
    tiling(shape), rowCount(rowCount), colCount(colCount), startTile(nullptr), destTile(nullptr)
{
    resizeGrid();
}

void SearchGrid::setRowAndColCount(uint rowCount, uint colCount)
{
    startTile.reset();
    destTile.reset();

    this->rowCount = rowCount;
    this->colCount = colCount;

    resizeGrid();
}

void SearchGrid::setStart(const SearchGrid::TileCoords &coord)
{
    startTile = at(coord);
    startTile->type = TileType::Start;
    startCoords = coord;
}

void SearchGrid::clearStart()
{
    startTile->type = TileType::Empty;
    startTile.reset();
}

void SearchGrid::setDest(const SearchGrid::TileCoords &coord)
{
    destTile = at(coord);
    destTile->type = TileType::Destination;
    destCoords = coord;
}

void SearchGrid::clearDest()
{
    destTile->type = TileType::Empty;
    destTile.reset();
}

std::shared_ptr<Tile> SearchGrid::at(const SearchGrid::TileCoords &coord)
{
    if(coord.colNum >= 0 && coord.rowNum >= 0 && coord.colNum < colCount && coord.rowNum < rowCount)
        return tiles[coord.rowNum][coord.colNum];

    return nullptr;
}

void SearchGrid::resetMap()
{
    for(auto &row : tiles)
        for(auto &tile : row)
            if(tile->type == TileType::Visited || tile->type == TileType::Path) tile->type = TileType::Empty;
}

void SearchGrid::resizeGrid()
{
    tiles.clear();

    tiles.resize(rowCount);
    for(auto &row : tiles)
    {
        row.reserve(colCount);
        for(uint i = 0; i < colCount; i++){
            switch (tiling) {
                case Tiling::Rectangle:
                    row.append(std::make_shared<Rectangle>());
                    break;
                case Tiling::Hexagon:
                    row.append(std::make_shared<Hexagon>());
                    break;
                default:
                    qFatal("invalid direction passed as function argument");
            }
        }
    }
}
