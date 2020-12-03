#include "bfs.h"

BFS::BFS(SearchGrid &grid) : PathFinder(grid), dirIndex(4)
{

}


bool BFS::initialize()
{
    if(grid.startField && grid.destField)
    {
        qDebug() << "[BFS] initialzed" << Qt::endl;

        fieldsToCheck.push_back(grid.startCoords);
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
    if(fieldsToCheck.empty() && dirIndex == 4) return false;

    if(dirIndex == 4)
    {
        nextField = fieldsToCheck.front();
        fieldsToCheck.pop_front();
        dirIndex = 0;
    }

    Field *neighbor = nullptr;
    FieldCoords neighborCoords;
    while((!neighbor || neighbor->type != Field::Type::Empty) && dirIndex < 4)
    {
        neighborCoords = getNeighborCoords(nextField, PathFinder::directions[dirIndex]);
        neighbor = grid.at(neighborCoords);
        dirIndex++;
    }

    if(DEBUG_MSGS_ON) qDebug() << "[BFS] field row: " << nextField.rowNum << " col: " << nextField.colNum << Qt::endl;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] neigbor row: " << neighborCoords.rowNum << " col: " << neighborCoords.colNum << Qt::endl;

    if(neighbor && neighbor->type == Field::Type::Empty)
    {
        neighbor->type = Field::Type::Visited;
        fieldsToCheck.push_back(neighborCoords);
    }

    return true;
}

std::list<Field::Coordinates> BFS::getPath()
{
}
