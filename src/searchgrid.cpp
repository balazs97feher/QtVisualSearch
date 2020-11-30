#include "searchgrid.h"

SearchGrid::SearchGrid(uint rowCount, uint colCount) :
    rowCount(rowCount), colCount(colCount)
{
    fields.resize(rowCount);
    for(auto &row : fields)
    {
        row.resize(colCount);
        for(auto &field : row) field = FieldType::Empty;
    }
}

void SearchGrid::setRowAndColCount(uint rowCount, uint colCount)
{
    this->rowCount = rowCount;
    this->colCount = colCount;

    fields.clear();
    fields.resize(rowCount);
    for(auto &row : fields)
    {
        row.resize(colCount);
        for(auto &field : row) field = FieldType::Empty;
    }
}
