#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "debug.h"

#include <QWidget>
#include <QPaintEvent>
#include <QSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>

#include "canvas.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QSize windowSize;
    QVBoxLayout* verticalLayout;
    QHBoxLayout* controlArea;
    QTextEdit* rowCount;
    QPushButton* setRowAndColCount;
    QTextEdit* colCount;
    Canvas* canvas;

private slots:
    void rowOrColCountChanged();
};
#endif // MAINWINDOW_H
