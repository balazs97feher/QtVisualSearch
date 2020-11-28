#ifndef CANVAS_H
#define CANVAS_H

#include "debug.h"
#include <QWidget>
#include <QSize>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    uint rowCount;
    uint colCount;

signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QSize canvasSize;
};

#endif // CANVAS_H
