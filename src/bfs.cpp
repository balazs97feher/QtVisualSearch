#include "bfs.h"

BFS::BFS(SearchGrid &grid) : PathFinder(grid), dirIndex(4)
{
    previousField.resize(grid.rowCount);
    for(auto &row : previousField)
    {
        row.resize(grid.colCount);
        for(auto &p : row) p = nullptr;
    }
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

    while (!neighbor || (neighbor->type != FieldType::Empty && neighbor->type != FieldType::Destination))
    {
        if(dirIndex == 4)
        {
            if(fieldsToCheck.empty()) return false;
            currentField = fieldsToCheck.front();
            fieldsToCheck.pop_front();
            dirIndex = 0;
        }

        while((!neighbor || (neighbor->type != FieldType::Empty && neighbor->type != FieldType::Destination)) && dirIndex < 4)
        {
            neighborCoords = getNeighborCoords(currentField, PathFinder::directions[dirIndex]);
            neighbor = grid.at(neighborCoords);
            dirIndex++;
        }
    }

    previousField[neighborCoords.rowNum][neighborCoords.colNum] = grid.at(currentField);

    if(neighbor->type == FieldType::Destination)
    {
        if(DEBUG_MSGS_ON) qDebug() << "[BFS] reached destination" << Qt::endl;
        return false;
    }
    neighbor->type = FieldType::Visited;
    fieldsToCheck.push_back(neighborCoords);

    static uint visitId = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[BFS] visited new neighbor " << visitId++ << Qt::endl;

    return true;
}

std::list<Field::Coordinates> BFS::getPath()
{
}
