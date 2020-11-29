#ifndef SEARCHGRID_H
#define SEARCHGRID_H

#include <QVector>

class Canvas;

class SearchGrid
{
    friend class Canvas;

public:
    SearchGrid(uint rowCount, uint colCount);

private:
    QVector<QVector<int>> fields;
    uint rowCount, colCount;
};

#endif // SEARCHGRID_H
