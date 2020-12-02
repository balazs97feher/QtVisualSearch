#include "bfs.h"

BFS::BFS(SearchGrid &grid) : PathFinder(grid)
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
    static uint direction = 0;

    auto nextField = fieldsToCheck.front();
    fieldsToCheck.pop_front();

//    switch (direction) {

//    }

    return true;
}

std::list<Field::Coordinates> BFS::getPath()
{
}
