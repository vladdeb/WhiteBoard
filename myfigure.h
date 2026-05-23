#pragma once
#ifndef MYFIGURE_H
#define MYFIGURE_H

#include <QPoint>
#include <QPen>
#include <QPaintDevice>
#include <cstdint>
#include <QJsonObject>

enum Types {
    tpLine,
    tpRect,
    tpEllipse,
    tpText,
    tpCurve,
    tpDrag
};

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
    virtual Types type() { return Types::tpDrag; }

    virtual QJsonObject toJson();
    virtual void fromJson(const QJsonObject &json);
};

#endif // MYFIGURE_H
