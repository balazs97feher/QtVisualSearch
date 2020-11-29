#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QRectF>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent), rowCount(9), colCount(16)
{
    fields.resize(rowCount);
    for(auto &row : fields) row.resize(colorCount());
}

void Canvas::setRowAndColCount(uint rowCount, uint colCount)
{
    this->rowCount = rowCount;
    this->colCount = colCount;
    rectWidth = float(canvasSize.width())/colCount;
    rectHeight = float(canvasSize.height())/rowCount;

    fields.clear();
    fields.resize(rowCount);
    for(auto &row : fields) row.resize(colorCount());
}


void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);

    for(uint i = 0; i < rowCount; i++)
    {
        for(uint j = 0; j < colCount; j++){
            QRectF rect(j*rectWidth, i*rectHeight, rectWidth, rectHeight);
            if(fields[i][j] == 1) painter.setBrush(Qt::red);
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
    rectWidth = float(canvasSize.width())/colCount;
    rectHeight = float(canvasSize.height())/rowCount;

    if(DEBUG_MSGS_ON) qDebug() << "Canvas resize: " << canvasSize.width() << '/' << canvasSize.height() << Qt::endl;
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    int row = event->localPos().y() / rectHeight;
    int col = event->localPos().x() / rectWidth;
    fields[row][col] = 1;

    update();

    if(DEBUG_MSGS_ON) qDebug() << event->localPos().x() << '/' << event->localPos().y() << Qt::endl;
}
