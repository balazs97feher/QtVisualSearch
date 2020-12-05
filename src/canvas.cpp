#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPaintEvent>

Canvas::Canvas(SearchGrid &searchGrid) : QWidget(nullptr), searchGrid(searchGrid), dragAndDrawWalls(false)
{

}

void Canvas::setRowAndColCount(uint rowCount, uint colCount)
{
    searchGrid.setRowAndColCount(rowCount, colCount);

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
            switch (searchGrid.fields[i][j].type) {
                case FieldType::Empty:
                    painter.setBrush(Qt::green);
                break;
                case FieldType::Wall:
                    painter.setBrush(Qt::red);
                break;
                case FieldType::Start:
                    painter.setBrush(Qt::blue);
                break;
                case FieldType::Destination:
                    painter.setBrush(Qt::black);
                break;
                case FieldType::Visited:
                    painter.setBrush(Qt::yellow);
                break;
                case FieldType::Path:
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
        if(searchGrid.at(clickCoord).type == FieldType::Empty)
            searchGrid.at(clickCoord).type = FieldType::Wall;
        else if(searchGrid.at(clickCoord).type == FieldType::Wall)
            searchGrid.at(clickCoord).type = FieldType::Empty;

        update();
    }
    else dragAndDrawWalls = false;

    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse release " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto clickCoord = getCoord(*event);

    if(!searchGrid.startField)
    {
        searchGrid.setStart(clickCoord);
    }
    else if(!searchGrid.destField)
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

Canvas::FieldCoords Canvas::getCoord(const QMouseEvent &event) const
{
    FieldCoords coord;
    coord.rowNum = uint(event.localPos().y() / rectHeight);
    coord.colNum = uint(event.localPos().x() / rectWidth);

    return coord;
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(DEBUG_MSGS_ON) qDebug() << "[Canvas] mouse move " << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;

    auto cursorCoord = getCoord(*event);

    auto &field = searchGrid.at(cursorCoord);
    if(field.type == FieldType::Empty)
    {
        field.type = FieldType::Wall;
        dragAndDrawWalls = true;
    }

    update();
}
