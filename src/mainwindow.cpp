#include "mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), windowSize(1600, 900)
{
    resize(windowSize);
    verticalLayout = std::make_unique<QVBoxLayout>();
    controlArea = new QHBoxLayout();
    controlArea->setAlignment(Qt::AlignLeft);
    verticalLayout->addLayout(controlArea);
    canvas = new Canvas();
    verticalLayout->addWidget(canvas);

    rowCount = new QLineEdit("9");
    colCount = new QLineEdit("16");
    rowCount->setFixedSize(30, 25);
    rowCount->setAlignment(Qt::AlignCenter);
    colCount->setAlignment(Qt::AlignCenter);
    colCount->setFixedSize(30, 25);
    intValidator = std::make_unique<QIntValidator>(0, 99);
    rowCount->setValidator(intValidator.get());
    colCount->setValidator(intValidator.get());

    setRowAndColCount = new QPushButton("Set");
    setRowAndColCount->setFixedSize(60, 25);

    algorithmList = new QComboBox();
    algorithmList->insertItem(0, "BFS");
    algorithmList->setFixedSize(60, 25);
    startSearch = new QPushButton("Start");
    startSearch->setFixedSize(60, 25);

    controlArea->addWidget(colCount);
    controlArea->addWidget(rowCount);
    controlArea->addWidget(setRowAndColCount);
    controlArea->addWidget(algorithmList);
    controlArea->addWidget(startSearch);

    QObject::connect(setRowAndColCount, &QPushButton::clicked, this, &MainWindow::rowOrColCountChanged);
    QObject::connect(startSearch, &QPushButton::clicked, this, &MainWindow::runAlgorithm);

    setLayout(verticalLayout.get());
}

MainWindow::~MainWindow()
{

}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    windowSize = event->size();

    if(DEBUG_MSGS_ON) qDebug() << "[MainWindow] resize: " << windowSize.width() << '/' << windowSize.height() << Qt::endl;
}

void MainWindow::rowOrColCountChanged()
{
    canvas->setRowAndColCount(rowCount->text().toUInt(), colCount->text().toUInt());

    update();

    if(DEBUG_MSGS_ON) qDebug() << "[MainWindow] colCount : " << colCount->text()
                               << " rowCount: " << rowCount->text() << Qt::endl;
}

void MainWindow::runAlgorithm()
{

}
