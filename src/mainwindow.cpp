#include "mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QTimer>
#include <QMessageBox>
#include "bfs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), windowSize(1600, 900), searchGrid(make_shared<SearchGrid>(27, 48, SearchGrid::Tiling::Rectangle)),
      stepInterval(100), algoFinished(false)
{ 
    resize(windowSize);
    verticalLayout = std::make_unique<QVBoxLayout>();
    controlArea = new QHBoxLayout();
    controlArea->setAlignment(Qt::AlignLeft);
    verticalLayout->addLayout(controlArea);
    canvas = new Canvas(searchGrid);
    verticalLayout->addWidget(canvas);

    tilingList = new QComboBox();
    tilingList->setFixedSize(100, 25);
    tilingList->addItem("Rectangle tiling");
    tilingList->addItem("Hexagon tiling");

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

    slider = new QSlider(Qt::Orientation::Horizontal);
    slider->setFixedSize(120, 25);
    slider->setTickInterval(10);
    slider->setMinimum(0);
    slider->setMaximum(190);
    slider->setValue(200 - stepInterval.count());

    controlArea->addWidget(tilingList);
    controlArea->addWidget(colCount);
    controlArea->addWidget(rowCount);
    controlArea->addWidget(setRowAndColCount);
    controlArea->addWidget(algorithmList);
    controlArea->addWidget(startSearch);
    controlArea->addWidget(slider);

    connect(setRowAndColCount, &QPushButton::clicked, this, &MainWindow::rowOrColCountChanged);
    connect(startSearch, &QPushButton::clicked, this, &MainWindow::startAlgorithm);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::setStepInterval);
    connect(tilingList, SIGNAL(currentIndexChanged(int)), this, SLOT(setTiling(int)));

    setLayout(verticalLayout.get());

    setWindowIcon(QIcon(":/vsicon.png"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    windowSize = event->size();
}

void MainWindow::rowOrColCountChanged()
{
    auto rowCnt = rowCount->text().toUInt();
    auto colCnt = colCount->text().toUInt();
    searchGrid->setRowAndColCount(rowCnt, colCnt);
    canvas->resize();

    update();
}

void MainWindow::startAlgorithm()
{
    switch (algorithmList->currentIndex()) {
        case 0:
            algorithm = std::make_shared<BFS>(searchGrid);
            break;
    }

    if(algoFinished) searchGrid->resetMap();
    update();

    if(algorithm->initialize())
    {
        connect(&timer, &QTimer::timeout, this, &MainWindow::advanceAlgorithm);
        timer.start(stepInterval);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Please set a start and a destination tile.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

void MainWindow::advanceAlgorithm()
{
    if(algorithm->advance()) update();
    else
    {
        timer.stop();
        disconnect(&timer, nullptr, nullptr, nullptr);

        path = algorithm->getPath();
        if(!path.empty())
        {
            connect(&timer, &QTimer::timeout, this, &MainWindow::drawPath);
            timer.start(stepInterval);
        } else algoFinished = true;
    }
}

void MainWindow::drawPath()
{
    if(!path.empty())
    {
        auto step = path.front();
        path.pop_front();

        searchGrid->at(step)->type = Tile::Type::Path;
        update();
    }
    else
    {
        timer.stop();
        disconnect(&timer, nullptr, nullptr, nullptr);
        path.clear();
        algorithm.reset();
        algoFinished = true;
    }
}

void MainWindow::setStepInterval()
{
    stepInterval = std::chrono::milliseconds(200 - slider->value());
    if(timer.isActive()) timer.start(stepInterval);
}

void MainWindow::setTiling(int index)
{
    searchGrid.reset();
    verticalLayout->removeWidget(canvas);
    delete canvas;

    auto rowCnt = rowCount->text().toUInt();
    auto colCnt = colCount->text().toUInt();

    switch(index)
    {
        case 0:
            searchGrid = make_unique<SearchGrid>(rowCnt, colCnt, SearchGrid::Tiling::Rectangle);
            break;
        case 1:
            searchGrid = make_unique<SearchGrid>(rowCnt, colCnt, SearchGrid::Tiling::Hexagon);
            break;
    }
    canvas = new Canvas(searchGrid);

    verticalLayout->addWidget(canvas);
    update();
}
