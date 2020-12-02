#include "bfs.h"

BFS::BFS(SearchGrid &grid) : PathFinder(grid), dirIndex(0)
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
    if(fieldsToCheck.empty()) return false;

    if(dirIndex == 0)
    {
        nextField = fieldsToCheck.front();
        fieldsToCheck.pop_front();
    }

    Field *neighbor = nullptr;
    FieldCoords neighborCoords;

    while(neighbor == nullptr)
    {
        neighborCoords = getNeighborCoords(nextField, directions[dirIndex]);
        neighbor = grid.at(neighborCoords);
        dirIndex = (dirIndex + 1) % 4;
    }

    if(neighbor->type == Field::Type::Empty)
    {
        neighbor->type = Field::Type::Visited;
        fieldsToCheck.push_back(neighborCoords);
    }

    return true;
}

std::list<Field::Coordinates> BFS::getPath()
{
}
