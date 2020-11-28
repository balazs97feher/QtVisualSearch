#include "canvas.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{

}


void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect(canvasSize.width()/4, canvasSize.height()/4, canvasSize.width()/2, canvasSize.height()/2);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);
    painter.setBrush(QColor(150,200,200));
    painter.drawRect(rect);

    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "Canvas paint: " << id++ << Qt::endl;
}


void Canvas::resizeEvent(QResizeEvent *event)
{
    canvasSize = event->size();

    if(DEBUG_MSGS_ON) qDebug() << "Canvas resize: " << canvasSize.width() << '/' << canvasSize.height() << Qt::endl;
}
