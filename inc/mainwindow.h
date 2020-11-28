#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "debug.h"

#include <QWidget>
#include <QPaintEvent>
#include <QSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>

#include "canvas.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QSize windowSize;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* controlArea;
    QTextEdit* rowCount;
    QTextEdit* colCount;
    Canvas* canvas;
};
#endif // MAINWINDOW_H
