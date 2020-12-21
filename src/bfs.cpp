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
        qDebug() << "[BFS] initialzed" << Qt::endl;

        tilesToCheck.push_back(grid->startCoords);
        return true;
    }
    else
    {
        qDebug() << "[BFS] failed to initilaze" << Qt::endl;
        return false;
    }
}

bool BFS::advance()
{
    static uint callId = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] advance called " << callId++ << Qt::endl;

    if(tilesToCheck.empty() && dirIndex == directionCount) return false;

    shared_ptr<Tile> neighbor;
    TileCoords neighborCoords;

    while (!neighbor || (neighbor->type != TileType::Empty && neighbor->type != TileType::Destination))
    {
        if(DEBUG_MSGS_ON) qDebug() << "[BFS] OUTER " << dirIndex << Qt::endl;
        if(dirIndex == directionCount)
        {
            if(tilesToCheck.empty()) return false;
            if(DEBUG_MSGS_ON) qDebug() << "[BFS] poppin " << dirIndex << Qt::endl;
            currentTile = tilesToCheck.front();
            tilesToCheck.pop_front();
            dirIndex = 0;
        }

        while((!neighbor || (neighbor->type != TileType::Empty && neighbor->type != TileType::Destination)) && dirIndex < directionCount)
        {
            if(DEBUG_MSGS_ON) qDebug() << "[BFS] dir iter " << dirIndex << Qt::endl;
            neighborCoords = grid->tiles[0][0]->getNeighborCoords(currentTile, PathFinder::directions[dirIndex]);
            neighbor = grid->at(neighborCoords);
            dirIndex++;
        }
    }

    previousTile[neighborCoords.rowNum][neighborCoords.colNum] = currentTile;

    if(neighbor->type == TileType::Destination)
    {
        if(DEBUG_MSGS_ON) qDebug() << "[BFS] reached destination" << Qt::endl;
        return false;
    }
    neighbor->type = TileType::Visited;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] push back: " << neighborCoords.rowNum << ' ' << neighborCoords.colNum << Qt::endl;
    tilesToCheck.push_back(neighborCoords);

    static uint visitId = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] visited new neighbor " << visitId++ << Qt::endl;

    return true;
}

list<BFS::TileCoords> BFS::getPath()
{
    list<TileCoords> path;
    auto step = previousTile[grid->destCoords.rowNum][grid->destCoords.colNum];

    while(grid->at(step)->type != TileType::Start)
    {
        path.push_front(step);
        step = previousTile[step.rowNum][step.colNum];
    }

    return path;
}
