#include "searchgrid.h"

SearchGrid::SearchGrid(uint rowCount, uint colCount) :
    rowCount(rowCount), colCount(colCount), startField(nullptr), destField(nullptr)
{
    fields.resize(rowCount);
    for(auto &row : fields) row.resize(colCount);
}

void SearchGrid::setRowAndColCount(uint rowCount, uint colCount)
{
    startField = nullptr;
    destField = nullptr;

    this->rowCount = rowCount;
    this->colCount = colCount;

    fields.clear();
    fields.resize(rowCount);
    for(auto &row : fields) row.resize(colCount);
}

void SearchGrid::setStart(const SearchGrid::FieldCoords &coord)
{
    startField = at(coord);
    at(coord)->type = FieldType::Start;
    startCoords = coord;
}

void SearchGrid::clearStart()
{
    startField->type = FieldType::Empty;
    startField = nullptr;
}

void SearchGrid::setDest(const SearchGrid::FieldCoords &coord)
{
    destField = at(coord);
    at(coord)->type = FieldType::Destination;
    destCoords = coord;
}

void SearchGrid::clearDest()
{
    destField->type = FieldType::Empty;
    destField = nullptr;
}

Field* SearchGrid::at(const SearchGrid::FieldCoords &coord)
{
    if(coord.rowNum >= 0 && coord.colNum >= 0 && coord.colNum < colCount && coord.rowNum < rowCount)
        return &fields[coord.rowNum][coord.colNum];

    return nullptr;
}

void SearchGrid::resetMap()
{
    for(auto &row : fields)
        for(auto &field : row)
            if(field.type == FieldType::Visited || field.type == FieldType::Path) field.type = FieldType::Empty;
}
