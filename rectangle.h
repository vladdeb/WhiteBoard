#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "myfigure.h"


class Rectangle : public MyFigure
{
private:
    QPointF start, end;
public:
    Rectangle(QWidget *parent, QColor color, std::uint32_t width) : MyFigure(parent, color, width) {}
    void init(QPointF p) override;
    void draw(QPainter *painter) override;
    void drag(QPointF p) override;
    void finalize() override {}

    Types type() override;
    QJsonObject toJson() override;
    void fromJson(const QJsonObject& json) override;
};

#endif // RECTANGLE_H
