#include "searchgrid.h"
#include "square.h"

SearchGrid::SearchGrid(const uint rowCount, const uint colCount, const Tiling shape) :
    shape(shape), rowCount(rowCount), colCount(colCount), startTile(nullptr), destTile(nullptr)
{
    tiles.resize(rowCount);
    for(auto &row : tiles)
    {
        row.reserve(colCount);
        for(uint i = 0; i < colCount; i++){
            switch (shape) {
                case Tiling::Square:
                    row.append(std::make_shared<Square>());
                    break;
                default:
                    if(DEBUG_MSGS_ON) qDebug() << "[SearchGrid] this shape is not yet implemented." << Qt::endl;
            }
        }
    }
}

void SearchGrid::setRowAndColCount(uint rowCount, uint colCount)
{
    startTile.reset();
    destTile.reset();

    this->rowCount = rowCount;
    this->colCount = colCount;

    tiles.clear();
    tiles.resize(rowCount);
    for(auto &row : tiles)
    {
        row.reserve(colCount);
        for(uint i = 0; i < colCount; i++){
            switch (shape) {
                case Tiling::Square:
                    row.append(std::make_shared<Square>());
                    break;
                default:
                    if(DEBUG_MSGS_ON) qDebug() << "[SearchGrid] this shape is not yet implemented." << Qt::endl;
            }
        }
    }
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
    if(coord.rowNum >= 0 && coord.colNum >= 0 && coord.colNum < colCount && coord.rowNum < rowCount)
        return tiles[coord.rowNum][coord.colNum];

    return nullptr;
}

void SearchGrid::resetMap()
{
    for(auto &row : tiles)
        for(auto &tile : row)
            if(tile->type == TileType::Visited || tile->type == TileType::Path) tile->type = TileType::Empty;
}
