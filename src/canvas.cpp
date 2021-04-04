#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <QPaintEvent>
#include <algorithm>
#include <cmath>

using namespace std;

Canvas::Canvas(shared_ptr<SearchGrid> searchGrid) : QWidget(nullptr), searchGrid(searchGrid), dragAndDrawWalls(false)
{
    colors = {
        {TileType::Empty, QColor(0, 255, 0)},
        {TileType::Wall, QColor(255, 0, 0)},
        {TileType::Start, QColor(0, 0, 255)},
        {TileType::Destination, QColor(0, 0, 0)},
        {TileType::Visited, QColor(255, 255, 0)},
        {TileType::Path, QColor(255, 255, 255)}
    };
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);

    switch(searchGrid->tiling)
    {
        case SearchGrid::Tiling::Rectangle:
            paintRectangles(painter);
            break;
        case SearchGrid::Tiling::Hexagon:
            paintHexagons(painter);
            break;
    }
}

void Canvas::paintRectangles(QPainter &painter)
{
    for(uint i = 0; i < searchGrid->rowCount; i++)
    {
        for(uint j = 0; j < searchGrid->colCount; j++){
            QRectF rect(j*boundingWidth, i*boundingHeight, boundingWidth, boundingHeight);
            painter.setBrush(colors[searchGrid->tiles[i][j]->type]);
            painter.drawRect(rect);
        }
    }
}

void Canvas::paintHexagons(QPainter &painter)
{
    const QVector<QPointF> vertices = {
        {0.5 * boundingWidth, 0},
        {boundingWidth, 0.25 * boundingHeight},
        {boundingWidth, 0.75 * boundingHeight},
        {0.5 * boundingWidth, boundingHeight},
        {0, 0.75 * boundingHeight},
        {0, 0.25 * boundingHeight}
    };
    const QPolygonF upperLeft(vertices);

    for(uint i = 0; i < searchGrid->rowCount; i++)
    {
        auto offsetHex = (i % 2 == 0) ? upperLeft : upperLeft.translated(0.5 * boundingWidth, 0);

        for(uint j = 0; j < searchGrid->colCount; j++)
        {
            auto translated = offsetHex.translated(j * boundingWidth, i * 0.75 * boundingHeight);
            painter.setBrush(colors[searchGrid->tiles[i][j]->type]);
            painter.drawConvexPolygon(translated);
        }
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    resize();
}

void Canvas::resize()
{
    switch (searchGrid->tiling) {
        case SearchGrid::Tiling::Rectangle:
            boundingWidth = float(size().width()) / searchGrid->colCount;
            boundingHeight = float(size().height()) / searchGrid->rowCount;
            break;
        case SearchGrid::Tiling::Hexagon:
            boundingWidth = searchGrid->rowCount == 1 ? float(size().width()) / searchGrid->colCount
                                                     : float(2 * size().width()) / (2 * searchGrid->colCount + 1);
            boundingHeight = float(4 * size().height()) / (3 * searchGrid->rowCount + 1);
            break;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);

    if(!dragAndDrawWalls && searchGrid->at(clickCoord) != nullptr)
    {
        if(searchGrid->at(clickCoord)->type == TileType::Empty)
            searchGrid->at(clickCoord)->type = TileType::Wall;
        else if(searchGrid->at(clickCoord)->type == TileType::Wall)
            searchGrid->at(clickCoord)->type = TileType::Empty;

        update();
    }
    else dragAndDrawWalls = false;
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);
    if(searchGrid->at(clickCoord) != nullptr)
    {
        if(!searchGrid->startTile) searchGrid->setStart(clickCoord);
        else if(!searchGrid->destTile) searchGrid->setDest(clickCoord);
        else
        {
            searchGrid->clearStart();
            searchGrid->clearDest();
        }

        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    auto cursorCoord = getCoord(*event);

    auto tile = searchGrid->at(cursorCoord);
    if(tile != nullptr && tile->type == TileType::Empty)
    {
        tile->type = TileType::Wall;
        dragAndDrawWalls = true;
        update();
    }
}

Canvas::TileCoords Canvas::getCoord(const QMouseEvent &event) const
{
    switch(searchGrid->tiling)
    {
        case SearchGrid::Tiling::Rectangle:
            return getRectangleCoord(event.localPos());
        case SearchGrid::Tiling::Hexagon:
            return getHexagonCoord(event.localPos());
    }
}

Canvas::TileCoords Canvas::getRectangleCoord(const QPointF &point) const
{
    TileCoords coord;
    coord.rowNum = floor(point.y() / boundingHeight);
    coord.colNum = floor(point.x() / boundingWidth);

    return coord;
}

Canvas::TileCoords Canvas::getHexagonCoord(const QPointF &point) const
{
    TileCoords coord;

    int estimatedRowNum = floor(point.y() / (0.75 * boundingHeight));

    QPointF offsetPoint = point;
    if(estimatedRowNum % 2 == 1) offsetPoint.setX(point.x() - 0.5 * boundingWidth);

    int estimatedColNum = floor(offsetPoint.x() / boundingWidth);

    // transform point coordinates into the bounding rectangle's local coordinates
    offsetPoint.setX(offsetPoint.x() - estimatedColNum * boundingWidth);
    offsetPoint.setY(offsetPoint.y() - estimatedRowNum * 0.75 * boundingHeight);
    if(offsetPoint.y() < 0.25 * boundingHeight)
    {
        // check if point is above the hexagon's top triangle
        auto m = (0.25 * boundingHeight) / (0.5 * boundingWidth);
        if(offsetPoint.x() < 0.5 * boundingWidth)
        {
            if(offsetPoint.y() < (-m * offsetPoint.x() + 0.25 * boundingHeight))
            {
                if(estimatedRowNum % 2 == 0) estimatedColNum = estimatedColNum - 1;
                estimatedRowNum = estimatedRowNum - 1;
            }
        }
        else
        {
            if(offsetPoint.y() < (m * offsetPoint.x() - 0.25 * boundingHeight))
            {
                if(estimatedRowNum % 2 == 1) estimatedColNum = estimatedColNum + 1;
                estimatedRowNum = estimatedRowNum - 1;
            }
        }
    }

    coord.rowNum = estimatedRowNum;
    coord.colNum = estimatedColNum;
    return coord;
}
