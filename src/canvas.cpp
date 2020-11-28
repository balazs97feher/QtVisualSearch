#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent), rowCount(9), colCount(16)
{

}


void Canvas::paintEvent(QPaintEvent *event)
{
    const uint rectWidth = canvasSize.width()/colCount;
    const uint rectHeight = canvasSize.height()/rowCount;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);
    painter.setBrush(QColor(150,200,200));

    for(uint i = 0; i < rowCount; i++)
    {
        for(uint j = 0; j < colCount; j++){
            painter.drawRect(j*rectWidth, i*rectHeight, rectWidth, rectHeight);
        }
    }

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "Canvas paint: " << id++ << Qt::endl;
}


void Canvas::resizeEvent(QResizeEvent *event)
{
    canvasSize = event->size();

    if(DEBUG_MSGS_ON) qDebug() << "Canvas resize: " << canvasSize.width() << '/' << canvasSize.height() << Qt::endl;
}
