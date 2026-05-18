#pragma once
#ifndef MYFIGURE_H
#define MYFIGURE_H

#include <QPoint>
#include <QPen>
#include <QPaintDevice>
#include <cstdint>

class MyFigure
{
protected:
    std::uint32_t _width;
    QColor _color;
    QPen pen;
    QWidget *_parent;
public:
    MyFigure(QWidget *parent, QColor color, std::uint32_t width);
    virtual void init(QPointF p) {}
    virtual void draw(QPainter *painter) {}
    virtual void drag(QPointF p) {}
    virtual void finalize() {}
};

#endif // MYFIGURE_H
