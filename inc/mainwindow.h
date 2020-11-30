#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "debug.h"

#include <QWidget>
#include <QPaintEvent>
#include <QSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <memory>

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
    std::unique_ptr<QVBoxLayout> verticalLayout;
    QHBoxLayout* controlArea;
    QLineEdit* colCount;
    QLineEdit* rowCount;
    std::unique_ptr<QIntValidator> intValidator;
    QPushButton* setRowAndColCount;
    Canvas* canvas;

private slots:
    void rowOrColCountChanged();
};
#endif // MAINWINDOW_H
