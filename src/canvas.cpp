#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPaintEvent>
#include <algorithm>

Canvas::Canvas(SearchGrid &searchGrid) : QWidget(nullptr), searchGrid(searchGrid), dragAndDrawWalls(false)
{

}

void Canvas::setRowAndColSize(uint rowCount, uint colCount)
{
    rectWidth = float(canvasSize.width())/searchGrid.colCount;
    rectHeight = float(canvasSize.height())/searchGrid.rowCount;
}


void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);

    for(uint i = 0; i < searchGrid.rowCount; i++)
    {
        for(uint j = 0; j < searchGrid.colCount; j++){
            QRectF rect(j*rectWidth, i*rectHeight, rectWidth, rectHeight);
            switch (searchGrid.tiles[i][j]->type) {
                case TileType::Empty:
                    painter.setBrush(Qt::green);
                break;
                case TileType::Wall:
                    painter.setBrush(Qt::red);
                break;
                case TileType::Start:
                    painter.setBrush(Qt::blue);
                break;
                case TileType::Destination:
                    painter.setBrush(Qt::black);
                break;
                case TileType::Visited:
                    painter.setBrush(Qt::yellow);
                break;
                case TileType::Path:
                    painter.setBrush(Qt::white);
                break;
            }
            painter.drawRect(rect);
        }
    }

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] paint " << id++ << Qt::endl;
}


void Canvas::resizeEvent(QResizeEvent *event)
{
    canvasSize = event->size();
    rectWidth = float(canvasSize.width())/searchGrid.colCount;
    rectHeight = float(canvasSize.height())/searchGrid.rowCount;

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] resize " << canvasSize.width() << '/' << canvasSize.height() << Qt::endl;
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

    if(!searchGrid.startTile)
    {
        searchGrid.setStart(clickCoord);
    }
    else if(!searchGrid.destTile)
    {
        searchGrid.setDest(clickCoord);
    }
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
    coord.rowNum = std::max(0.0, std::min(double(searchGrid.rowCount - 1), event.localPos().y() / rectHeight));
    coord.colNum = std::max(0.0, std::min(double(searchGrid.colCount - 1), event.localPos().x() / rectWidth));

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
