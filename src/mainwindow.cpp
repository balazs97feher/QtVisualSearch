#include "mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <Qt>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), windowSize(1600, 900)
{
    resize(windowSize);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    static int id = 0;
    auto type = event->type();
    qDebug() << type << id++ << Qt::endl;

    QPainter painter(this);
    QRect rect1(windowSize.width()/4,windowSize.height()/4,windowSize.width()/2,windowSize.height()/2);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(100,100,100));
    painter.setPen(pen);
    painter.setBrush(QColor(150,200,200));
    painter.drawRect(rect1);
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    windowSize = event->size();
    qDebug() << windowSize.width() << '/' << windowSize.height() << Qt::endl;
}
