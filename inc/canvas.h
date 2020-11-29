#ifndef CANVAS_H
#define CANVAS_H

#include "debug.h"
#include "searchgrid.h"
#include <QWidget>
#include <QSize>
#include <QVector>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void setRowAndColCount(uint rowCount, uint colCount);

signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QSize canvasSize;
    float rectWidth, rectHeight;
    SearchGrid searchGrid;

};

#endif // CANVAS_H
