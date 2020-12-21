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
    explicit Canvas(std::shared_ptr<SearchGrid> searchGrid);
    void resize();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QSize canvasSize;
    std::shared_ptr<SearchGrid> searchGrid;
    float boundingWidth, boundingHeight;
    bool dragAndDrawWalls;
    QHash<Tile::Type, QColor> colors;

    void paintRectangles(QPainter& painter);
    void paintHexagons(QPainter &painter);
    TileCoords getCoord(const QMouseEvent& event) const;
    TileCoords getRectangleCoord(const QPointF &point) const;
    TileCoords getHexagonCoord(const QPointF &point) const;

};

#endif // CANVAS_H
