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
    static uint callId = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] advance called " << callId++ << Qt::endl;

    if(fieldsToCheck.empty() && dirIndex == 4) return false;

    Field *neighbor = nullptr;
    FieldCoords neighborCoords;

    while (!neighbor || neighbor->type != Field::Type::Empty)
    {
        if(dirIndex == 4)
        {
            if(fieldsToCheck.empty()) return false;
            nextField = fieldsToCheck.front();
            fieldsToCheck.pop_front();
            dirIndex = 0;
        }

        while((!neighbor || neighbor->type != Field::Type::Empty) && dirIndex < 4)
        {
            neighborCoords = getNeighborCoords(nextField, PathFinder::directions[dirIndex]);
            neighbor = grid.at(neighborCoords);
            dirIndex++;
        }
    }

    neighbor->type = Field::Type::Visited;
    fieldsToCheck.push_back(neighborCoords);

    static uint visitId = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] visited new neighbor " << visitId++ << Qt::endl;

    return true;
}

std::list<Field::Coordinates> BFS::getPath()
{
}
