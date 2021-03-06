#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QComboBox>
#include <QTimer>
#include <QSlider>
#include <memory>
#include <chrono>

#include "canvas.h"
#include "searchgrid.h"
#include "pathfinder.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QSize windowSize;
    std::unique_ptr<QVBoxLayout> verticalLayout;
    QHBoxLayout *controlArea;
    QComboBox *tilingList;
    QLineEdit *colCount;
    QLineEdit *rowCount;
    std::unique_ptr<QIntValidator> intValidator;
    QPushButton *setRowAndColCount;
    QComboBox *algorithmList;
    QPushButton *startSearch;
    Canvas* canvas;
    std::shared_ptr<SearchGrid> searchGrid;
    std::shared_ptr<PathFinder> algorithm;
    std::list<Tile::Coordinates> path;
    QTimer timer;
    std::chrono::milliseconds stepInterval;
    QSlider *slider;

    bool algoFinished;

private slots:
    void rowOrColCountChanged();
    void startAlgorithm();
    void advanceAlgorithm();
    void drawPath();
    void setStepInterval();
    void setTiling(int index);
};
#endif // MAINWINDOW_H
