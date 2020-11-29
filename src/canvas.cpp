#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent), searchGrid(9, 16)
{

}

void Canvas::setRowAndColCount(uint rowCount, uint colCount)
{
    searchGrid.rowCount = rowCount;
    searchGrid.colCount = colCount;
    rectWidth = float(canvasSize.width())/searchGrid.colCount;
    rectHeight = float(canvasSize.height())/searchGrid.rowCount;

    searchGrid.fields.clear();
    searchGrid.fields.resize(rowCount);
    for(auto &row : searchGrid.fields) row.resize(colorCount());
}


void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);

    for(uint i = 0; i < searchGrid.rowCount; i++)
    {
        for(uint j = 0; j < searchGrid.colCount; j++){
            QRectF rect(j*rectWidth, i*rectHeight, rectWidth, rectHeight);
            if(searchGrid.fields[i][j] == 1) painter.setBrush(Qt::red);
            else painter.setBrush(Qt::green);
            painter.drawRect(rect);
        }
    }

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "Canvas paint: " << id++ << Qt::endl;
}


void Canvas::resizeEvent(QResizeEvent *event)
{
    canvasSize = event->size();
    rectWidth = float(canvasSize.width())/searchGrid.colCount;
    rectHeight = float(canvasSize.height())/searchGrid.rowCount;

    if(DEBUG_MSGS_ON) qDebug() << "Canvas resize: " << canvasSize.width() << '/' << canvasSize.height() << Qt::endl;
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    int row = event->localPos().y() / rectHeight;
    int col = event->localPos().x() / rectWidth;
    searchGrid.fields[row][col] = 1;

    update();

    if(DEBUG_MSGS_ON) qDebug() << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}
