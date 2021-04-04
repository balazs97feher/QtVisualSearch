#include "bfs.h"

using namespace::std;

BFS::BFS(shared_ptr<SearchGrid> grid) : PathFinder(grid)
{
    previousTile.resize(grid->rowCount);
    for(auto &row : previousTile) row.resize(grid->colCount);

    directions = grid->tiles[0][0]->getDirections();
    directionCount = directions.size();
    dirIndex = directionCount;
}


bool BFS::initialize()
{
    if(grid->startTile && grid->destTile)
    {
        tilesToCheck.push_back(grid->startCoords);
        return true;
    }
    else
    {
        return false;
    }
}

bool BFS::advance()
{
    if(tilesToCheck.empty() && dirIndex == directionCount) return false;

    shared_ptr<Tile> neighbor;
    TileCoords neighborCoords;

    while (!neighbor || (neighbor->type != TileType::Empty && neighbor->type != TileType::Destination))
    {
        if(dirIndex == directionCount)
        {
            if(tilesToCheck.empty()) return false;
            currentTile = tilesToCheck.front();
            tilesToCheck.pop_front();
            dirIndex = 0;
        }

        neighborCoords = grid->tiles[0][0]->getNeighborCoords(currentTile, PathFinder::directions[dirIndex]);
        neighbor = grid->at(neighborCoords);
        dirIndex++;
    }

    previousTile[neighborCoords.rowNum][neighborCoords.colNum] = currentTile;

    if(neighbor->type == TileType::Destination)
    {
        return false;
    }
    neighbor->type = TileType::Visited;
    tilesToCheck.push_back(neighborCoords);

    return true;
}

list<BFS::TileCoords> BFS::getPath()
{
    if(previousTile[grid->destCoords.rowNum][grid->destCoords.colNum].rowNum == -1) return {};

    list<TileCoords> path;
    auto step = previousTile[grid->destCoords.rowNum][grid->destCoords.colNum];
    while(grid->at(step)->type != TileType::Start)
    {
        path.push_front(step);
        step = previousTile[step.rowNum][step.colNum];
    }

    return path;
}
