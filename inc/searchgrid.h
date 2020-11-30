#ifndef SEARCHGRID_H
#define SEARCHGRID_H

#include <QVector>

class Canvas;

class SearchGrid
{
    friend class Canvas;

    enum class FieldType
    {
        Empty,
        Wall,
        Start,
        Destination
    };

public:
    SearchGrid(uint rowCount, uint colCount);
    void setRowAndColCount(uint rowCount, uint colCount);

private:
    QVector<QVector<FieldType>> fields;
    uint rowCount, colCount;
};

#endif // SEARCHGRID_H
