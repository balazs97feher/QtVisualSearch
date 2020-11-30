#ifndef SEARCHGRID_H
#define SEARCHGRID_H

#include "field.h"
#include <QVector>

class Canvas;

class SearchGrid
{
    friend class Canvas;
    using FieldType = Field::Type;
    using FieldCoords = Field::Coordinates;

public:
    SearchGrid(uint rowCount, uint colCount);
    void setRowAndColCount(uint rowCount, uint colCount);
    void setStart(const FieldCoords &coord);
    void clearStart();
    void setDest(const FieldCoords &coord);
    void clearDest();
    Field& at(const FieldCoords &coord);

private:
    QVector<QVector<Field>> fields;
    uint rowCount, colCount;

    Field *startField, *destField;
};

#endif // SEARCHGRID_H
