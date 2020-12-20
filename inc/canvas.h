#ifndef CANVAS_H
#define CANVAS_H

#include "debug.h"
#include "searchgrid.h"
#include <QWidget>
#include <QSize>
#include <QVector>
#include <QHash>

class Canvas : public QWidget
{
    Q_OBJECT

    using TileType = Tile::Type;
    using TileCoords = Tile::Coordinates;

public:
    explicit Canvas(SearchGrid &searchGrid);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QSize canvasSize;
    SearchGrid &searchGrid;
    float boundingWidth, boundingHeight;
    bool dragAndDrawWalls;
    QHash<Tile::Type, QColor> colors;

    TileCoords getCoord(const QMouseEvent& event) const;

};

#endif // CANVAS_H
