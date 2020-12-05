#include "mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QTimer>
#include <QMessageBox>
#include "bfs.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), windowSize(1600, 900), searchGrid(27, 48)
{
    resize(windowSize);
    verticalLayout = std::make_unique<QVBoxLayout>();
    controlArea = new QHBoxLayout();
    controlArea->setAlignment(Qt::AlignLeft);
    verticalLayout->addLayout(controlArea);
    canvas = new Canvas(searchGrid);
    verticalLayout->addWidget(canvas);

    rowCount = new QLineEdit("27");
    colCount = new QLineEdit("48");
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
    QObject::connect(startSearch, &QPushButton::clicked, this, &MainWindow::startAlgorithm);

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

void MainWindow::startAlgorithm()
{
    switch (algorithmList->currentIndex()) {
        case 0:
        algorithm = std::make_shared<BFS>(searchGrid);
        break;
    }

    if(algorithm->initialize())
    {
        connect(&timer, &QTimer::timeout, this, &MainWindow::advanceAlgorithm);
        timer.start(100);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Please set a start and a destination field.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

void MainWindow::advanceAlgorithm()
{
    if(algorithm->advance())
    {
        update();
    }
    else
    {
        timer.stop();
        disconnect(&timer, nullptr, nullptr, nullptr);

        path = algorithm->getPath();
        connect(&timer, &QTimer::timeout, this, &MainWindow::drawPath);
        timer.start(100);
    }
}

void MainWindow::drawPath()
{
    if(!path.empty())
    {
        auto step = path.front();
        path.pop_front();

        searchGrid.at(step)->type = Field::Type::Path;
        update();
    }
    else
    {
        timer.stop();
        disconnect(&timer, nullptr, nullptr, nullptr);
        path.clear();
        algorithm.reset();
    }
}
