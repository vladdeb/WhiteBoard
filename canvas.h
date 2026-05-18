#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include "myfigure.h"
#include "factory.h"

#include <QWidget>
#include <QVector>
#include <QMouseEvent>

class Canvas : public QWidget
{
private:
    QVector<MyFigure*> figures = {};
    double _xMin, _xMax;
    double _yMin, _yMax;
    double scaleX, scaleY;
    Factory factory;
    MyFigure *tool = nullptr;
    Types toolType = Types::tpDrag;
    QColor _color = Qt::white;
    std::uint32_t _width = 2;
    QPoint prevPos;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override { scaleX = width() / (_xMax - _xMin); scaleY = height() / (_yMax - _yMin); }
    void setBorders(double xMin, double xMax, double yMin, double yMax);
public:
    explicit Canvas(QWidget *parent = nullptr) : QWidget(parent) { factory = Factory(); setBorders(0, width(), 0, height()); }
    ~Canvas() {
        for(auto figure: figures) {
            delete figure;
        }
    }
    void setTool(Types type);
    void setColor(QColor c) { _color = c; }
    void setWidth(std::uint32_t w) { _width = w; }
    QPoint toScreen(QPointF);
    QPointF  toWorld(QPoint);
    double getScaleX() { return scaleX; }
    double getScaleY() { return scaleY; }
    double getXMin() { return _xMin; }
    double getXMax() { return _xMax; }
    double getYMin() { return _yMin; }
    double getYMax() { return _yMax; }
};

#endif // CANVAS_H
