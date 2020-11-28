#include "mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), windowSize(1600, 900)
{
    resize(windowSize);
    verticalLayout = new QVBoxLayout();
    controlArea = new QHBoxLayout();
    controlArea->setAlignment(Qt::AlignLeft);
    verticalLayout->addLayout(controlArea);
    canvas = new Canvas();
    verticalLayout->addWidget(canvas);
    rowCount = new QTextEdit("4");
    colCount = new QTextEdit("5");
    rowCount->setFixedSize(100,30);
    colCount->setFixedSize(100,30);
    controlArea->addWidget(rowCount);
    controlArea->addWidget(colCount);

    setLayout(verticalLayout);
}

MainWindow::~MainWindow()
{
    delete verticalLayout;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    static int id = 0;
    if(DEBUG_MSGS_ON) qDebug() << "MainWindow paint: " << id++ << Qt::endl;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    windowSize = event->size();

    if(DEBUG_MSGS_ON) qDebug() << "MainWindow resize: " << windowSize.width() << '/' << windowSize.height() << Qt::endl;
}
