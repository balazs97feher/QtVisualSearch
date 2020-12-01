#include "bfs.h"

BFS::BFS(SearchGrid &grid) : PathFinder(grid)
{

}


bool BFS::initialize()
{
    if(grid.startField && grid.destField)
    {
        qDebug() << "[BFS] initialzed" << Qt::endl;
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
}

std::list<Field::Coordinates> BFS::getPath()
{
}
