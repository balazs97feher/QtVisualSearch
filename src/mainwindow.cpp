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

    rowCount = new QTextEdit("9");
    colCount = new QTextEdit("16");
    rowCount->setFixedSize(100,30);
    colCount->setFixedSize(100,30);
    setRowAndColCount = new QPushButton("Set");
    setRowAndColCount->setFixedSize(50, 30);

    controlArea->addWidget(colCount);
    controlArea->addWidget(rowCount);
    controlArea->addWidget(setRowAndColCount);

    QObject::connect(setRowAndColCount, &QPushButton::clicked, this, &MainWindow::rowOrColCountChanged);

    setLayout(verticalLayout);
}

MainWindow::~MainWindow()
{
    delete verticalLayout;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    windowSize = event->size();

    if(DEBUG_MSGS_ON) qDebug() << "[MainWindow] resize: " << windowSize.width() << '/' << windowSize.height() << Qt::endl;
}

void MainWindow::rowOrColCountChanged()
{
    canvas->setRowAndColCount(rowCount->toPlainText().toUInt(), colCount->toPlainText().toUInt());

    update();

    if(DEBUG_MSGS_ON) qDebug() << "[MainWindow] colCount : " << colCount->toPlainText()
                               << " rowCount: " << rowCount->toPlainText() << Qt::endl;
}
