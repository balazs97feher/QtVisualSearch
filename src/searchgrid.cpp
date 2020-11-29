#include "searchgrid.h"

SearchGrid::SearchGrid(uint rowCount, uint colCount) :
    rowCount(rowCount), colCount(colCount)
{
    fields.resize(rowCount);
    for(auto &row : fields) row.resize(colCount);
}
