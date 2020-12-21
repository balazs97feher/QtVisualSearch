#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPolygonF>
#include <QPaintEvent>
#include <algorithm>

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

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] paint " << id++ << Qt::endl;
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
        {boundingWidth / 2, 0},
        {boundingWidth, boundingHeight / 4},
        {boundingWidth, 3 * boundingHeight / 4},
        {boundingWidth / 2, boundingHeight},
        {0, 3 * boundingHeight / 4},
        {0, boundingHeight / 4}
    };
    const QPolygonF upperLeft(vertices);

    for(uint i = 0; i < searchGrid->rowCount; i++)
    {
        auto offsetHex = (i % 2 == 0) ? upperLeft : upperLeft.translated(boundingWidth / 2, 0);

        for(uint j = 0; j < searchGrid->colCount; j++)
        {
            auto translated = offsetHex.translated(j * boundingWidth, i * 3 * boundingHeight / 4);
            painter.setBrush(colors[searchGrid->tiles[i][j]->type]);
            painter.drawConvexPolygon(translated);
        }
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    resize();

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] resize " << size().width() << '/' << size().height() << Qt::endl;
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

    if(!dragAndDrawWalls)
    {
        if(searchGrid->at(clickCoord)->type == TileType::Empty)
            searchGrid->at(clickCoord)->type = TileType::Wall;
        else if(searchGrid->at(clickCoord)->type == TileType::Wall)
            searchGrid->at(clickCoord)->type = TileType::Empty;

        update();
    }
    else dragAndDrawWalls = false;

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse release " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);

    if(!searchGrid->startTile) searchGrid->setStart(clickCoord);
    else if(!searchGrid->destTile) searchGrid->setDest(clickCoord);
    else
    {
        searchGrid->clearStart();
        searchGrid->clearDest();
    }

    update();

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] double click " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse move " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;

    auto cursorCoord = getCoord(*event);

    auto tile = searchGrid->at(cursorCoord);
    if(tile->type == TileType::Empty)
    {
        tile->type = TileType::Wall;
        dragAndDrawWalls = true;
    }

    update();
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
    coord.rowNum = std::max(0.0, std::min(double(searchGrid->rowCount - 1), point.y() / boundingHeight));
    coord.colNum = std::max(0.0, std::min(double(searchGrid->colCount - 1), point.x() / boundingWidth));

    return coord;
}

Canvas::TileCoords Canvas::getHexagonCoord(const QPointF &point) const
{
    // TODO: weird behavior at the edges -> maybe change uint row/colNum to int and hangle in SearchGrid::at

    int estimatedRowNum = std::max(0.0, std::min(double(searchGrid->rowCount - 1), point.y() / (0.75 * boundingHeight)));

    QPointF offsetPoint = point;
    if(estimatedRowNum % 2 == 1) offsetPoint.setX(point.x() - boundingWidth / 2);

    int estimatedColNum = std::max(0.0, std::min(double(searchGrid->colCount - 1), offsetPoint.x() / boundingWidth));

    // transform point coordinates into the bounding rectangle's local coordinates
    offsetPoint.setX(offsetPoint.x() - estimatedColNum * boundingWidth);
    offsetPoint.setY(offsetPoint.y() - estimatedRowNum * 0.75 * boundingHeight);

//    if(DEBUG_MSGS_ON) qDebug() << "[Coord] row " << estimatedRowNum << " col " << estimatedColNum << Qt::endl;
    if(DEBUG_MSGS_ON) qDebug() << "[Coord] y " << offsetPoint.y() << " x " << offsetPoint.x() << Qt::endl;

    if(offsetPoint.y() < 0.25 * boundingHeight)
    {
        // check if point is above the hexagon's top triangle
        auto m = (0.25 * boundingHeight) / (0.5 * boundingWidth);
        if(offsetPoint.x() < boundingWidth / 2)
        {
            if(DEBUG_MSGS_ON) qDebug() << "[Coord] 1" << Qt::endl;
            if(offsetPoint.y() < (-m * offsetPoint.x() + 0.25 * boundingHeight))
            {
                if(DEBUG_MSGS_ON) qDebug() << "[Coord] 2" << Qt::endl;
                if(estimatedRowNum % 2 == 0)
                {
                    if(DEBUG_MSGS_ON) qDebug() << "[Coord] 3" << Qt::endl;
                    estimatedColNum = std::max(0, std::min(int(searchGrid->colCount - 1), estimatedColNum - 1));
                }
                estimatedRowNum = std::max(0, std::min(int(searchGrid->rowCount - 1), estimatedRowNum - 1));
            }
        }
        else
        {
            if(DEBUG_MSGS_ON) qDebug() << "[Coord] 4" << Qt::endl;
            if(offsetPoint.y() < (m * offsetPoint.x() - 0.25 * boundingHeight))
            {
                if(DEBUG_MSGS_ON) qDebug() << "[Coord] 5" << Qt::endl;
                if(estimatedRowNum % 2 == 1)
                {
                    if(DEBUG_MSGS_ON) qDebug() << "[Coord] 6" << Qt::endl;
                    estimatedColNum = std::max(0, std::min(int(searchGrid->colCount - 1), estimatedColNum + 1));
                }
                estimatedRowNum = std::max(0, std::min(int(searchGrid->rowCount - 1), estimatedRowNum - 1));
            }
        }
    }

    TileCoords coord;
    coord.rowNum = estimatedRowNum;
    coord.colNum = estimatedColNum;

    return coord;
}
