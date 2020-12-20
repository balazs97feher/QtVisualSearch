#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPaintEvent>
#include <algorithm>

Canvas::Canvas(SearchGrid &searchGrid) : QWidget(nullptr), searchGrid(searchGrid), dragAndDrawWalls(false)
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

//    boundingWidth = float(size().width())/searchGrid.colCount;
//    boundingHeight = float(size().height())/searchGrid.rowCount;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);

    for(uint i = 0; i < searchGrid.rowCount; i++)
    {
        for(uint j = 0; j < searchGrid.colCount; j++){
            QRectF rect(j*boundingWidth, i*boundingHeight, boundingWidth, boundingHeight);
            painter.setBrush(colors[searchGrid.tiles[i][j]->type]);
            painter.drawRect(rect);
        }
    }

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] paint " << id++ << Qt::endl;
}


void Canvas::resizeEvent(QResizeEvent *event)
{
    switch (searchGrid.tiling) {
        case SearchGrid::Tiling::Rectangle:
            boundingWidth = float(size().width())/searchGrid.colCount;
            boundingHeight = float(size().height())/searchGrid.rowCount;
            break;
    }

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] resize " << size().width() << '/' << size().height() << Qt::endl;
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);

    if(!dragAndDrawWalls)
    {
        if(searchGrid.at(clickCoord)->type == TileType::Empty)
            searchGrid.at(clickCoord)->type = TileType::Wall;
        else if(searchGrid.at(clickCoord)->type == TileType::Wall)
            searchGrid.at(clickCoord)->type = TileType::Empty;

        update();
    }
    else dragAndDrawWalls = false;

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse release " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);

    if(!searchGrid.startTile) searchGrid.setStart(clickCoord);
    else if(!searchGrid.destTile) searchGrid.setDest(clickCoord);
    else
    {
        searchGrid.clearStart();
        searchGrid.clearDest();
    }

    update();

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] double click " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}

Canvas::TileCoords Canvas::getCoord(const QMouseEvent &event) const
{
    TileCoords coord;
    coord.rowNum = std::max(0.0, std::min(double(searchGrid.rowCount - 1), event.localPos().y() / boundingHeight));
    coord.colNum = std::max(0.0, std::min(double(searchGrid.colCount - 1), event.localPos().x() / boundingWidth));

    return coord;
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse move " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;

    auto cursorCoord = getCoord(*event);

    auto tile = searchGrid.at(cursorCoord);
    if(tile->type == TileType::Empty)
    {
        tile->type = TileType::Wall;
        dragAndDrawWalls = true;
    }

    update();
}
