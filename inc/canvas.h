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

    using FieldType = Field::Type;
    using FieldCoords = Field::Coordinates;

public:
    explicit Canvas(SearchGrid &searchGrid);

    void setRowAndColCount(uint rowCount, uint colCount);

signals:

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QSize canvasSize;
    float rectWidth, rectHeight;
    SearchGrid &searchGrid;
    bool dragAndDrawWalls;

    FieldCoords getCoord(const QMouseEvent& event) const;

};

#endif // CANVAS_H
